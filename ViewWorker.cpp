#include <QDebug>
#include "ViewWorker.h"
#include "ui_ViewWorker.h"
#include "CustomListitem.h"
#include "EventWidget.h"
#include "ViewPrint.h"
#include "ViewEvent.h"
#include "ViewSchedule.h"
#include "ViewDocument.h"
#include "FiredDateDialog.h"
#include "NewSchedule.h"
#include "NewDocument.h"
#include "NewEvent.h"
#include "event.h"
#include "schedule.h"
#include "worker.h"
#include "document.h"
#include "statics.h"
#include "QMessageBox"
#include "CalendarPrint.h"

ViewWorker::ViewWorker(Worker *Worker, const QList<class Facility*> &Facilities, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    facilities(Facilities),
    scheduleCount(0),
    ui(new Ui::ViewWorker)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    this->setFocus();

    ui->CalendarWidget->subscribe(ui->Documents);

    ui->Surname->setText(worker->getSurName());
    ui->Name->setText(worker->getName());
    ui->Birthname->setText(worker->getBirthName());
    ui->PlaceOfBirth->setText(worker->getPlaceOfBirth());
    ui->Citizenship->setText(worker->getCitizenship());
    ui->Address->setText(worker->getAddress());
    ui->Town->setText(worker->getTown());
    ui->Zip->setText(worker->getZip());
    ui->Birthdate->setDate(worker->getBirthDate());
    ui->Phone->setText(worker->getPhone());
    ui->EMail->setText(worker->getEmail());
    ui->fire->setAutoDefault(false);
    ui->printCalendar->setAutoDefault(false);

    QList<QString> SEX;
    SEX.append("Мужской");
    SEX.append("Женский");
    ui->Sex->setSelection(SEX);
    ui->Sex->select(SEX[int(worker->getSex()) - 1]);

    QList<QString> FIRM;
    FIRM.append("ELID");
    FIRM.append("ELID_SP");
    ui->Firm->setSelection(FIRM);
    ui->Firm->select(FIRM[int(worker->getFirm()) - 1]);

    QList<QString> STATUS;
    STATUS.append("Неженатый");
    STATUS.append("Женатый");
    STATUS.append("Разведенный");
    STATUS.append("Вдовец");
    ui->Status->setSelection(STATUS);
    ui->Status->select(STATUS[int(worker->getStatus()) - 1]);

    if(worker->isFired()) {
        ui->fire->hide();
        ui->FiredAt->setDate(worker->getFiredAt());
        ui->CalendarWidget->setFunctionsUntil(worker->getFiredAt());
    }
    else {
        ui->FiredAt->hide();
        ui->labelFired->hide();
    }

    for(auto document : worker->getDocuments()) {
        CustomListitem *newDocument = new CustomListitem(document->getName() + "-" + document->getExpirationDate().toString("dd.MM.yyyy"),document->getID(), document->getExpirationDate(), this);
        connect(newDocument, SIGNAL(doubleClicked(long long)), this, SLOT(viewDocument(long long)));
        newDocument->compareWithDate(QDate::currentDate(), ui->Documents->getErgentToTop());
        ui->Documents->addItem(newDocument);
    }

    for(auto event : worker->getEvents()) {
        CustomListitem *newEvent = new CustomListitem(event->getName(),event->getID(),this);
        connect(newEvent, SIGNAL(doubleClicked(long long)), this, SLOT(viewEvent(long long)));
        ui->Events->addItem(newEvent);
    }

    for(auto schedule : worker->getSchedules()) {
        CustomListitem *newSchedule = new CustomListitem(schedule->getBeginsOnDate().toString("dd/MM/yyyy") + " - " + schedule->getEndsOnDate().toString("dd/MM/yyyy"), schedule->getID(), this);
        connect(newSchedule, SIGNAL(doubleClicked(long long)), this, SLOT(viewSchedule(long long)));
        ui->Schedules->addItem(newSchedule);
    }

    ui->CalendarWidget->setEvents(worker->getEvents());
    ui->CalendarWidget->setSchedules(worker->getSchedules());
    ui->CalendarWidget->subscribe(ui->EventDisplayWidget);
    ui->CalendarWidget->subscribe(this);
}

void ViewWorker::on_save_clicked()
{
    ui->save->setFocus();
    worker->setName(ui->Name->getText());
    worker->setSurname(ui->Surname->getText());
    worker->setBirthName(ui->Birthname->getText());
    worker->setPlaceOfBirth(ui->PlaceOfBirth->getText());
    worker->setCitizenship(ui->Citizenship->getText());
    worker->setAddress(ui->Address->getText());
    worker->setTown(ui->Town->getText());
    worker->setZip(ui->Zip->getText());
    worker->setBirthdate(ui->Birthdate->getDate());
    worker->setPhone(ui->Phone->getText());
    worker->setEmail(ui->EMail->getText());
    worker->setStatus(static_cast<MaritalStatus>(ui->Status->getValue()));
    worker->setFirm(static_cast<Firm>(ui->Firm->getValue()));
    worker->setSex(static_cast<Sex>(ui->Sex->getValue()));
    close();
}

void ViewWorker::on_print_clicked()
{
    ViewPrint window(worker, this);
    window.setModal(true);
    window.exec();
}


void ViewWorker::on_cansel_clicked()
{
    close();
}

void ViewWorker::on_removeDocument_clicked()
{
    long long id = ui->Documents->getSelectedItemID();
    worker->removeScans(id);
    removeDocument(id);
}

void ViewWorker::on_removeEvent_clicked()
{
    long long id = ui->Events->getSelectedItemID();
    removeEvent(id);
}

void ViewWorker::on_removeSchedule_clicked()
{
    long long id = ui->Schedules->getSelectedItemID();
    removeSchedule(id);
}

void ViewWorker::on_viewSchedule_clicked()
{
    long long id = ui->Schedules->getSelectedItemID();
    viewSchedule(id);
}

void ViewWorker::viewSchedule(long long ID)
{
    if(ID != CustomListWidget::invalidID) {
        for(auto schedule : worker->getSchedules()) {
            if(schedule->getID() == ID) {
                ViewSchedule window(schedule, facilities, this);
                window.setModal(true);
                window.exec();
                if(window.result()) {
                    auto scheduleCopy = new Schedule(*schedule);
                    removeSchedule(ID);
                    addSchedule(scheduleCopy);
                }
                break;
            }
        }
    }
    else {
        qDebug("Something went wrong!");
    }
}

void ViewWorker::on_viewEvent_clicked()
{
    long long id = ui->Events->getSelectedItemID();
    viewEvent(id);
}

void ViewWorker::viewEvent(long long ID)
{
    if(ID != CustomListWidget::invalidID) {
        for(auto event : worker->getEvents()) {
            if(event->getID() == ID) {
                ViewEvent window(event, this);
                window.setModal(true);
                window.exec();
                auto eventCopy = new Event(*event);
                removeEvent(ID);
                addEvent(eventCopy);
                break;
            }
        }
    }
    else {
        qDebug("Something went wrong!");
    }
}

void ViewWorker::on_viewDocument_clicked()
{
    long long id = ui->Documents->getSelectedItemID();
    viewDocument(id);
}

void ViewWorker::viewDocument(long long ID)
{
    if(ID != CustomListWidget::invalidID) {
        for(auto document : worker->getDocuments()) {
            if(document->getID() == ID) {
                ViewDocument window(document, this);
                window.setModal(true);
                window.exec();
                auto documentCopy = new Document(*document);
                removeDocument(ID);
                addDocument(documentCopy);
                break;
            }
        }
    }
    else {
        qDebug("Something went wrong!");
    }
}

void ViewWorker::on_addSchedule_clicked()
{
    Schedule* tempSchedule = new Schedule();

    NewSchedule window(tempSchedule, worker->getSchedules(), facilities, this);
    window.setModal(true);
    window.exec();

    if(tempSchedule->getFacilityID() == -1) {
        qDebug("Schedule Was NOT created\n");
        delete tempSchedule;
    }
    else {
            addSchedule(tempSchedule);
    }
}

void ViewWorker::on_addEvent_clicked()
{
    Event* tempEvent = new Event();
    tempEvent->setBeginsOn(ui->CalendarWidget->getSelectedDate());
    NewEvent window(tempEvent);
    window.setModal(true);
    window.exec();

    if(tempEvent->getName().isEmpty()) {
        qDebug("Event Was NOT created\n");
        delete tempEvent;
    }
    else {
        addEvent(tempEvent);
    }
    ui->CalendarWidget->setEvents(worker->getEvents());
    ui->CalendarWidget->setUpEvents();
}

void ViewWorker::on_addDocument_clicked()
{
    Document* tempDocument = new Document(worker->getID(), "workers");
    NewDocument window(tempDocument);
    window.setModal(true);
    window.exec();

    if(tempDocument->getName().isEmpty()) {
        qDebug("Document Was NOT created\n");
        delete tempDocument;
    }
    else {
        addDocument(tempDocument);
    }
}

void ViewWorker::on_fire_clicked()
{
    QDate* FiredAtDate = new QDate;
    FiredDateDialog window(FiredAtDate, ui->CalendarWidget->getSelectedDate(), this);
    window.setModal(true);
    window.exec();

    if(FiredAtDate->isValid()) {
        ui->fire->hide();

        worker->setFired(*FiredAtDate);
        ui->FiredAt->setDate(worker->getFiredAt());
        ui->CalendarWidget->setFunctionsUntil(worker->getFiredAt());
        ui->CalendarWidget->setUpCalendar();

        delete FiredAtDate;

        ui->labelFired->show();
        ui->FiredAt->show();
    }
}

void ViewWorker::on_work_rest_calculated(const int WorkDays, const int RestDays)
{
    ui->workDays->setText(QString::number(WorkDays));
    ui->restDays->setText(QString::number(RestDays));
}

void ViewWorker::addDocument(Document* NewDocument)
{
    worker->addDocument(NewDocument);
    CustomListitem* Document = new CustomListitem(NewDocument->getName() + "-" + NewDocument->getExpirationDate().toString("dd.MM.yyyy"), NewDocument->getID(), NewDocument->getExpirationDate(), this);
    connect(Document, SIGNAL(doubleClicked(long long)), this, SLOT(viewDocument(long long)));
    ui->Documents->addItem(Document);
    Document->compareWithDate(QDate::currentDate(), ui->Documents->getErgentToTop());
}

void ViewWorker::addEvent(Event* newEvent)
{
    worker->addEvent(newEvent);
    CustomListitem* Event = new CustomListitem(newEvent->getName(), newEvent->getID(), this);
    connect(Event, SIGNAL(doubleClicked(long long)), this, SLOT(viewEvent(long long)));
    ui->Events->addItem(Event);
}

void ViewWorker::addSchedule(Schedule *NewSchedule)
{
    worker->addSchedule(NewSchedule);
    CustomListitem* Schedule = new CustomListitem(NewSchedule->getBeginsOnDate().toString("dd/MM/yyyy") + " - " + NewSchedule->getEndsOnDate().toString("dd/MM/yyyy"), NewSchedule->getID(), this);
    connect(Schedule, SIGNAL(doubleClicked(long long)), this, SLOT(viewSchedule(long long)));
    ui->Schedules->addItem(Schedule);
    ui->CalendarWidget->setSchedules(worker->getSchedules());
}

void ViewWorker::removeDocument(const long long ID)
{
    worker->removeDocument(ID);
    ui->Documents->removeItemByID(ID);
}

void ViewWorker::removeEvent(const long long ID)
{
    worker->removeEvent(ID);
    ui->Events->removeItemByID(ID);
    ui->CalendarWidget->setEvents(worker->getEvents());
}

void ViewWorker::removeSchedule(long long ID)
{
    worker->removeSchedule(ID);
    ui->Schedules->removeItemByID(ID);
    ui->Schedules->repaint();
    ui->CalendarWidget->setSchedules(worker->getSchedules());
}

ViewWorker::~ViewWorker()
{
    delete ui;
}

void ViewWorker::on_printCalendar_clicked()
{
    CalendarPrint window(worker->getNameAndSurname(), ui->CalendarWidget->getSelectedDate(), worker->getFiredAt(), worker->getSchedules(), this);
    printWidget(window.window(), this);
}
