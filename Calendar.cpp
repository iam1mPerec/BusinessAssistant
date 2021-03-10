#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QDate>
#include <QDebug>
#include "Calendar.h"
#include "CalendarDate.h"
#include "CalendarDateObserver.h"
#include "CalendarObserver.h"
#include "CustomListWidget.h"
#include "EnumDateType.h"
#include "event.h"
#include "schedule.h"
#include "statics.h"



Calendar::Calendar(QWidget *parent) : QWidget(parent),
currentDate(QDate::currentDate()),
workDays(0),
restDays(0)
{
    dateObserver = new CalendarDateObserver(this);
    calendarObserver = new CalendarObserver();
    CalendarLayout = new QGridLayout();
    CalendarLayout->setSpacing(2);
    CalendarLayout->setContentsMargins(0, 10, 0, 10);

//    button to move to the privious month
    buttonLeft  = new QPushButton("<", this);
    buttonLeft->setAutoDefault(false);
    buttonLeft->setMaximumWidth(CalendarDate::getButtonSize());
    connect(buttonLeft, SIGNAL(released()),this, SLOT(buttonLeftClicked()));

//    button to move to the next month
    buttonRight = new QPushButton(">", this);
    buttonRight->setAutoDefault(false);
    buttonRight->setMaximumWidth(CalendarDate::getButtonSize());
    connect(buttonRight, SIGNAL(released()),this, SLOT(buttonRightClicked()));

    QPixmap PixMap (":/icons/today.png");
    QIcon TodayIcon(PixMap);
    buttonToday = new QPushButton(this);
    buttonToday->setIcon(TodayIcon);
    buttonToday->setAutoDefault(false);
    connect(buttonToday, SIGNAL(released()),this, SLOT(buttonTodayClicked()));

//    button to chose a month
    comboMonth = new QComboBox(this);
    comboMonth->addItems(QStringList() << "01 Januar" << "02 Februar" << "03 März" << "04 April" << "05 Mai" << "06 Juni" << "07 Juli" << "08 August" << "09 September" << "10 Oktober" << "11 November" << "12 Dezember" );
    connect(comboMonth, SIGNAL(activated(int)), this, SLOT (monthChanged()));
    comboMonth->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    comboMonth->setMaximumWidth(CalendarDate::getButtonSize()*2);

//    fuild to fill in the year
    lineYear = new QLineEdit(this);
    lineYear->setAlignment(Qt::AlignCenter);
    lineYear->setStyleSheet("color: black;");
    lineYear->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
    setYearValidator(lineYear);
    connect(lineYear, SIGNAL (returnPressed()),this, SLOT (yearChanged()));

    CalendarLayout->addWidget(buttonLeft, 0, 0, 1, 1);
    CalendarLayout->addWidget(comboMonth, 0, 1, 1, 2);
    CalendarLayout->addWidget(lineYear, 0, 3, 1, 2);
    CalendarLayout->addWidget(buttonToday, 0, 5, 1, 1);
    CalendarLayout->addWidget(buttonRight, 0, 6, 1, 1);

    QString DaysOfTheWeek[] = {"Mo","Di","Mi","Do","Fr","Sa","So"};

    for(int column = 0; column < 7; column++) {
        QLabel* label = new QLabel(DaysOfTheWeek[column], this);
        label->setAlignment(Qt::AlignCenter);
        label->setFixedWidth(CalendarDate::getButtonSize());
        DaysOfTheWeekLabels.push_back(label);
        CalendarLayout->addWidget(label, 1, column);
    }

    for(int row = 0; row < 6; row++) {
        for(int column = 0; column < 7; column++) {

            CalendarDate *date = new CalendarDate(this);
            date->addObserver(dateObserver);
            calendarDates.push_back(date);
            date->setFixedWidth(CalendarDate::getButtonSize());
            CalendarLayout->addWidget(date, row+2, column);
        }
    }

    selectedDate = currentDate;
    setLayout(CalendarLayout);
    setUpCalendar();
}

void Calendar::setUpCalendar(QDate &Date)
{

    comboMonth->setCurrentIndex(Date.month() - 1);
    lineYear->setText(QString::number(Date.year()));

    QDate FirstDay = Date.addDays(1 - Date.day());

    for (int day = 1; day < FirstDay.dayOfWeek(); day++) {
        calendarDates[FirstDay.dayOfWeek() - day -1]->setDate(FirstDay.addDays(-day));
        calendarDates[FirstDay.dayOfWeek() - day -1]->disable();
    }

    for(int day = 0; day < FirstDay.daysInMonth(); day++) {
        calendarDates[FirstDay.dayOfWeek() + day - 1]->setDate(FirstDay.addDays(day));
    }

    for(int day = FirstDay.dayOfWeek() + FirstDay.daysInMonth() - 1, i = 0; day < calendarDates.length(); day++, i++) {
        calendarDates[day]->setDate(FirstDay.addDays(FirstDay.daysInMonth() + i));
        calendarDates[day]->disable();
    }

    if(selectedDate.year() == currentDate.year() && selectedDate.month() == currentDate.month()) {
        toCurrentDate();
    }

    setUpEvents();
    setUpSchedules();
}

void Calendar::setFunctionsUntil(QDate FunctionsUntil)
{
    functionsUntil = FunctionsUntil;
    setUpCalendar();
}

void Calendar::setUpCalendar()
{
    setUpCalendar(selectedDate);
}

void Calendar::setUpEvents()
{
    for(auto date : calendarDates)
    {
        date->setState(false);
        for(auto event : events)
        {
            if(event->isRelevant(date->getDate()))
            {
                date->setState(true);
            }
        }
        date->toDefault();
    }
    notifySubscribers();
}

void Calendar::toCurrentDate()
{
    selectedDate = currentDate;

    //find the current date in calendar and simulate a click on it
    for(auto date : calendarDates) {
        if(date->getDate() == selectedDate) {
            date->simmulateClicked();
        }
    }
}

void Calendar::clearTypes()
{
    for(auto date : calendarDates) {
        date->setState(DateTypes::none);
    }
}

void Calendar::setChecked(bool checked)
{
    QDate SelectDate = getSelectedDate();
    for(auto date : calendarDates) {
        if(date->getDate() == SelectDate) {
            date->setChecked(checked);
        }
    }
}

void Calendar::setUpSchedules()
{
    this->workDays = 0;
    this->restDays = 0;
    clearTypes();
    if(!schedules.isEmpty())
    {
        for(auto date : calendarDates)
        {
            for(auto schedule : schedules)
            {
                switch (schedule->isRelevant(date->getDate(), functionsUntil)) {
                case DateTypes::work:
                    date->setState(DateTypes::work);
                    if(!date->isDisabled()) {
                        ++this->workDays;
                    }
                    break;
                case DateTypes::rest:
                    date->setState(DateTypes::rest);
                    if(!date->isDisabled()) {
                        ++this->restDays;
                    }
                    break;
                default:
                    break;
                }
            }
            date->toDefault();
        }
    }
    this->calendarObserver->onWorkRestCalculation(this->workDays, this->restDays);
    repaint();
}

void Calendar::notifySubscribers()
{
    if(calendarObserver) {

        QList<Event *> RelevantEvents;

        for(auto event : events) {
            if(event->isRelevant(selectedDate)) {
                RelevantEvents.push_back(event);
            }
        }
        calendarObserver->notifySubscribers(RelevantEvents, selectedDate);
    }
}

void Calendar::onDateClicked(CalendarDate *DateClicked)
{
    selectedDate = DateClicked->getDate();

    for(auto date : calendarDates) {
        if(date->getDate() != selectedDate) {
            date->diselect();
        }
        date->toDefault();
    }

    notifySubscribers();
}

void Calendar::subscribe(class EventDisplay * Sub)
{
    calendarObserver->subscribe(Sub);
    notifySubscribers();
}

void Calendar::subscribe(CustomListWidget *Sub)
{
    calendarObserver->subscribe(Sub);
    notifySubscribers();
}

void Calendar::subscribe(MainWindow *Sub)
{
    calendarObserver->subscribe(Sub);
    notifySubscribers();
}

void Calendar::subscribe(ViewFacility *Sub)
{
    calendarObserver->subscribe(Sub);
    notifySubscribers();
}

void Calendar::subscribe(ViewWorker *Sub)
{
    calendarObserver->subscribe(Sub, this->workDays, this->restDays);
}

QDate Calendar::getSelectedDate()
{
    return selectedDate;
}

CalendarDate *Calendar::getDateById(int ID)
{
    for(auto date : calendarDates) {
        if(date->getID() == ID) {
            return date;
        }
    }
    return nullptr;
}

void Calendar::buttonLeftClicked()
{
    selectedDate.setDate(selectedDate.addMonths(-1).year(), selectedDate.addMonths(-1).month(), 1);
    setUpCalendar();
}

void Calendar::buttonRightClicked()
{
    selectedDate.setDate(selectedDate.addMonths(1).year(), selectedDate.addMonths(1).month(), 1);
    setUpCalendar();
}

void Calendar::buttonTodayClicked()
{
    toCurrentDate();
    setUpCalendar();
}

void Calendar::yearChanged()
{
    QDate date;
    date.setDate(lineYear->text().toInt(), selectedDate.month(), 1);
    if(date.isValid()) {
        selectedDate.setDate(date.year(), date.month(), date.day());
        setUpCalendar();
    }
    else {
        qDebug("Wrong year entery!\n");
    }
}

void Calendar::monthChanged()
{
    selectedDate.setDate(selectedDate.year(), comboMonth->currentIndex() + 1, selectedDate.day());
    setUpCalendar();
}


void Calendar::setEvents(const QList<Event *> &value)
{
    events.clear();
    events = value;
    setUpEvents();
}

void Calendar::addEvents(const QList<Event *> &items)
{
    for(auto item : items) {
        events.append(item);
    }
    setUpEvents();
}

void Calendar::addEvent(Event *value)
{
    events.append(value);
    setUpEvents();
}

void Calendar::removeEvent(long long ID)
{
    for(auto event : events) {
        if(event->getID() == ID) {
            events.removeOne(event);
        }
    }
    setUpEvents();
    notifySubscribers();
}

void Calendar::setSchedules(const QList<Schedule *> &value)
{
    schedules.clear();
    schedules = value;
    setUpSchedules();
}

Calendar::~Calendar()
{
    delete CalendarLayout;
    delete dateObserver;
    delete buttonLeft;
    delete buttonRight;
    delete comboMonth;
    delete lineYear;
    delete calendarObserver;

    for(auto label : DaysOfTheWeekLabels) {
        delete label;
    }

    for(auto date : calendarDates) {
        delete date;
    }
    CalendarDate::resetCount();
}
