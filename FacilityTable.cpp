#include <QDate>
#include <QDebug>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QMouseEvent>
#include "FacilityTable.h"
#include "TableGroup.h"
#include "ui_FacilityTable.h"
#include "facility.h"
#include "worker.h"
#include "schedule.h"
#include "DraggableListItem.h"
#include "TableItem.h"
#include "statics.h"
//                                             yellow,     green,    purple,      red,      blue,     orange
const QList<QString> FacilityTable::colors = {"#FED23F", "#B5D33D", "#b19cd9", "#FF7258", "#97D5CF", "#FFA346" };

FacilityTable::FacilityTable(class Facility *Facility, const QList<class Worker*> &Workers, int Year, QWidget *parent) :
    QDialog(parent),
    selectionState(SelectionState::noneSelected),
    year(Year),
    scale(Scale::to1),
    workersMarked(0),
    ui(new Ui::FacilityTable),
    facility(Facility),
    workers(Workers)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui->facilityName->setText(facility->getName());
    setWindowTitle("Mondsee OMV");

    ui->months->setSpacing(1);
    ui->months->setMargin(1);

    QDate Date = QDate::currentDate();

    QLocale LocalName = QLocale::German;
    QString MonthFormat = "MMMM";
    QString DayFormat   = "d ddd";

    for(int month = 0; month < 12; month++) {
        Date.setDate(year, month + 1, 1);
        QVBoxLayout* layout = new QVBoxLayout;
        QWidget* widget = new QWidget(this);
        QLabel* label = new QLabel(LocalName.toString(Date, MonthFormat));
        layout->setSpacing(1);
        layout->setMargin(0);
        widget->setLayout(layout);
        label->setStyleSheet("background-color: white; padding: 2px; font-weight: bold; padding: 15px;");
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        for(int day = 0; day < 31; day++) {
            Date.setDate(year, month + 1, day + 1);
            TableItem* item = new TableItem(Date, facility->getMaxWorkers(), this);
            item->subscribe(this);
            itemsMap.insert(item->getDate(), item);
            itemsList.push_back(item);
            layout->addWidget(item);
        }
        ui->months->addWidget(widget);
        this->months.append(widget);
    }

    setSchedules();

    QList<QPushButton*> Buttons = ui->btn_selection_group->findChildren<QPushButton*>();

    for(auto btn : ui->btn_selection_group->findChildren<QPushButton*>()) {
        this->buttons.push_back(btn);
    }

    for(auto btn : this->buttons) {
        btn->setVisible(false);
        connect(btn, &QPushButton::clicked, [=]() { this->onSelectionClicked( buttons.indexOf(btn) ); });
    }

    ui->btn_scale_1->setChecked(true);
    ui->year->setMaximumWidth(80);
    ui->year->startYearValidation();
    ui->year->setText(QString::number(this->year));
    connect(ui->year, &EditableLine::focusOut, this, &FacilityTable::onYearChanged);
}

void FacilityTable::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        this->selectionState = SelectionState::noneSelected;
    }
    else {
        QDialog::mousePressEvent(event);
    }
}

void FacilityTable::onDateHoovered(const QDate &date) {
    if(selectionState == SelectionState::firstDateSelected) {
        QDate StartDate, EndDate;
        if(startDate < date) {
            StartDate = startDate;
            EndDate = date;
        }
        else {
            StartDate = date;
            EndDate = startDate;
        }
    }
}

void FacilityTable::hideSelectionBtns()
{
    for(auto btn : this->buttons) {
        btn->hide();
    }
}

void FacilityTable::showSelectionBtns(const int lastBtn)
{
    for (int i = 0; i < lastBtn; ++i) {
        this->buttons[i]->show();
    }
}

void FacilityTable::extractGroups(Schedule *schedule, Worker *worker) {
    Schedule ThisYearSchedule(*schedule);
     if(schedule->getBeginsOnDate().year() < year) {
        long long numberOfDays = schedule->getBeginsOnDate().daysTo(QDate(year,1,1));
        if(numberOfDays > 0) {
            numberOfDays = numberOfDays % (schedule->getWorkDays() + schedule->getRestDays());
            numberOfDays = schedule->getWorkDays() - numberOfDays;
            if(numberOfDays > 0) {
                createGroup(worker, QDate(year, 01, 01), numberOfDays);
            }
        }
        ThisYearSchedule.setBeginsOn(QDate(year, 01, 01).addDays(numberOfDays + schedule->getRestDays()));
    }

    if(schedule->getEndsOnDate().year() > year) {
        ThisYearSchedule.setEndsOn(QDate(year, 12, 31));
    }

    long long numberOfDays = ThisYearSchedule.getBeginsOnDate().daysTo(schedule->getEndsOnDate()) + 1;

    int daysInShift = ThisYearSchedule.getWorkDays() + ThisYearSchedule.getRestDays();

    int numberOfShifts = numberOfDays / daysInShift;
    int remainder = numberOfDays % daysInShift;
    if(remainder > schedule->getWorkDays()) {
        remainder = schedule->getWorkDays();
    }

    for(int i = 0; i < numberOfShifts; i++) {
        createGroup(worker, ThisYearSchedule.getBeginsOnDate().addDays(i * daysInShift), ThisYearSchedule.getWorkDays());
    }
    if(remainder) {
        createGroup(worker, ThisYearSchedule.getBeginsOnDate().addDays(numberOfShifts * daysInShift), remainder);
    }
}

void FacilityTable::createGroup(class Worker *worker, QDate begins, long long numOfDays) {
    int section = getBestSection(begins, begins.addDays(numOfDays));
    if(itemsMap[begins]) {
        itemsMap[begins]->setText(section, worker->getNameAndSurname());
    }
    for(int i = 0; i < numOfDays; ++i) {
        QString color = this->colors[getWorkersColor(worker->getID())];
        if(itemsMap[begins.addDays(i)]) {
            itemsMap[begins.addDays(i)]->setColor(section, color);
        }
    }
}

void FacilityTable::onSelectionClicked(int CurrentSelection)
{
    if(CurrentSelection < 0) {
        CurrentSelection = 0;
    }
    switch (this->scale) {
        case Scale::to2:
        if(CurrentSelection > 1) {
            CurrentSelection = 1;
        }
        showMonthFromTo(1 + (CurrentSelection)*6, (CurrentSelection + 1)*6);
        break;

        case Scale::to3:
        if(CurrentSelection > 2) {
            CurrentSelection = 2;
        }
        showMonthFromTo(1 + (CurrentSelection)*4, (CurrentSelection + 1)*4);
        break;

        case Scale::to12:
        if(CurrentSelection > 11) {
            CurrentSelection = 11;
        }
        showMonthFromTo(1 + CurrentSelection, 1 + CurrentSelection);
        break;

        default:
        this->showMonthFromTo(1,12);
        break;
    }
}

void FacilityTable::hideMonths()
{
    for(auto month : months) {
        month->hide();
    }
}

void FacilityTable::setSchedules()
{
    for(auto worker : workers) {
        QList<Schedule *> RelevantSchedules = worker->getRelevantSchedules(year, facility->getID());
        for(auto schedule : RelevantSchedules) {
            extractGroups(schedule, worker);
        }
    }
}

void FacilityTable::showMonthFromTo(const int Start, const int End)
{
    this->hideMonths();
    for(int i = Start -1; i < End; ++i) {
        this->months[i]->show();
    }
}

void FacilityTable::toggleSelectionState()
{
    if ( (selectionState == SelectionState::noneSelected) || (selectionState == SelectionState::secondDateSelected)) {
        selectionState = SelectionState::firstDateSelected;
    }
    else {
        selectionState = SelectionState::secondDateSelected;
    }
}

int FacilityTable::getBestSection(QDate Begin, QDate End) const
{
    if(Begin > End) {
        QDate PlaceHolder = Begin;
        Begin = End;
        End = PlaceHolder;
    }
    QDate date = Begin;
//    section value
    QMap<int, int> sections;
    for(int i = 0; i < facility->getMaxWorkers(); ++i) {
        sections.insert(i, 0);
    }
    while(date != End && date.year() == year) {
        for (int i = 0; i < facility->getMaxWorkers(); ++i) {
            if(itemsMap[date]->isFree(i)) {
                ++sections[i];
            }
        }
        date = date.addDays(1);
    }
    int bestSection = 0;
    int bestValue = 0;
    for (int i = 0; i < facility->getMaxWorkers(); ++i) {
        if(sections[i] > bestValue) {
            bestSection = i;
            bestValue = sections[bestSection];
        }
    }
    return bestSection;
}

Colors FacilityTable::getWorkersColor(long long ID)
{
    if(workerColors.contains(ID)) {
        return workerColors[ID];
    }
    else {
        switch(Colors(workersMarked % colors.count())) {
            case Colors::yellow:
                workerColors.insert(ID, Colors::yellow);
                break;
            case Colors::green:
                workerColors.insert(ID, Colors::green);
                break;
            case Colors::purple:
                workerColors.insert(ID, Colors::purple);
                break;
            case Colors::red:
                workerColors.insert(ID, Colors::red);
                break;
            case Colors::blue:
                workerColors.insert(ID, Colors::blue);
                break;
            default:
                workerColors.insert(ID, Colors::extra);
                break;
        }
    }
    ++workersMarked;
    return workerColors[ID];
}

FacilityTable::~FacilityTable()
{
    for(auto item : itemsMap) {
        delete item;
    }

    delete ui;
}



void FacilityTable::on_btn_scale_1_clicked()
{
    for(auto btn : this->buttons) {
        btn->setVisible(false);
    }
    scale = Scale::to1;
    onSelectionClicked(0);
}

void FacilityTable::on_btn_scale_2_clicked()
{
    this->hideSelectionBtns();
    showSelectionBtns(2);
    this->buttons[0]->setChecked(true);
    scale = Scale::to2;
    onSelectionClicked(0);
}

void FacilityTable::on_btn_scale_3_clicked()
{
    this->hideSelectionBtns();
    showSelectionBtns(3);
    this->buttons[0]->setChecked(true);
    scale = Scale::to3;
    onSelectionClicked(0);
}

void FacilityTable::on_btn_scale_12_clicked()
{
    showSelectionBtns(12);
    this->buttons[0]->setChecked(true);
    scale = Scale::to12;
    onSelectionClicked(0);
}

void FacilityTable::onYearChanged()
{
    year = ui->year->getText().toInt();
    this->itemsMap.clear();
    for(int month = 0; month < 12; month++) {
        for(int day = 0; day < 31; day++) {
            this->itemsList[month*31 + day]->setDate(QDate(year, month + 1, day + 1));
            this->itemsList[month*31 + day]->clear();
            itemsMap.insert(QDate(year, month + 1, day + 1), itemsList[month*31 + day]);
        }
    }
    setSchedules();
}


void FacilityTable::on_print_clicked()
{
    ui->year->whiten();
    ui->TableController->hide();
    printWidget(ui->Print, this);
    ui->TableController->show();
    ui->year->deWhiten();
}
