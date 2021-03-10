#include <QDebug>
#include <QMessageBox>
#include "NewWorker.h"
#include "ui_NewWorker.h"
#include "NewSchedule.h"
#include "ViewSchedule.h"
#include "NewDocument.h"
#include "ViewDocument.h"
#include "NewEvent.h"
#include "ViewEvent.h"
#include "CustomListitem.h"
#include "worker.h"
#include "document.h"
#include "event.h"
#include "schedule.h"
#include "statics.h"
#include "CalendarDate.h"

using namespace std;

NewWorker::NewWorker(class Worker *TempWorker, const QList<class Facility*> &Facilities, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWorker),
    worker(TempWorker),
    facilities(Facilities)
{
    ui->setupUi(this);
    setDayValidator(ui->BirthDateDay);
    setMonthValidator(ui->BirthDateMonth);
    setYearValidator(ui->BirthDateYear);

    ui->AddPassport->setAutoDefault(false);
    ui->AddContract->setAutoDefault(false);
    ui->addInsurance->setAutoDefault(false);
    ui->AddRegestry->setAutoDefault(false);
    ui->AddA1->setAutoDefault(false);
}

void NewWorker::on_cansel_clicked()
{
    this->close();
}

void NewWorker::on_save_clicked()
{
    if(isValidText(ui->Surname) && isValidText(ui->Name) && isValidText(ui->BirthName) && isValidText(ui->Citizenship) &&
            isValidDate(ui->BirthDateYear, ui->BirthDateMonth, ui->BirthDateDay) && isValidText(ui->PlaceOfBirth) &&
            isValidText(ui->Address) && isValidText(ui->Town) && isValidText(ui->Zip) &&
            isValidEnum(worker->getSex()) && isValidEnum(worker->getStatus()) && isValidEnum(worker->getFirm()) &&
            worker->hasFirm() && worker->hasGender() && worker->hasStatus())
    {
            worker->setName(ui->Name->text());
            worker->setSurname(ui->Surname->text());
            worker->setBirthName(ui->BirthName->text());
            worker->setBirthdate(QDate(ui->BirthDateYear->text().toInt(), ui->BirthDateMonth->text().toInt(), ui->BirthDateDay->text().toInt()));
            worker->setPlaceOfBirth(ui->PlaceOfBirth->text());
            worker->setCitizenship(ui->Citizenship->text());
            worker->setAddress(ui->Address->text());
            worker->setTown(ui->Town->text());
            worker->setZip(ui->Zip->text());
            worker->setPhone(ui->Phone->text());
            worker->setEmail(ui->EMail->text());

//          Adds a birth day event
            Event* birthDayEvent = new Event();
            birthDayEvent->setBeginsOn(worker->getBirthDate().addDays(-2));
            birthDayEvent->setEndsOn(worker->getBirthDate());
            birthDayEvent->setIsRecurring(true);
            birthDayEvent->setName("ДР " + worker->getNameAndSurname());
            birthDayEvent->setDescription("День Рождения " + worker->getNameAndSurname() + "\n" + birthDayEvent->getEndsOnDate().toString("dd/MM/yyyy"));
            worker->addEvent(birthDayEvent);

            accept();
    }
}

bool NewWorker::openAddDocument(QString Preset)
{
    Document* tempDocument = new Document(worker->getID(), "workers");
    NewDocument window(tempDocument);
    window.setName(Preset);
    window.setModal(true);
    window.exec();

    if(tempDocument->getName().isEmpty()) {
        qDebug()<<"Document Was NOT created\n";
        delete tempDocument;
        return false;
    }
    else {
        worker->addDocument(tempDocument);
        CustomListitem* Document = new CustomListitem(tempDocument->getName(), tempDocument->getName(), this);
        ui->Documents->addItem(Document);
        return true;
    }
}

void NewWorker::on_addDocument_clicked()
{
    openAddDocument("");
}

void NewWorker::on_AddPassport_clicked()
{
    bool result = openAddDocument("Паспорт");
    if(result) {
        ui->AddPassport->hide();
    }
}

void NewWorker::on_AddContract_clicked()
{
    bool result = openAddDocument("Контракт");
    if(result) {
        ui->AddContract->hide();
    }
}

void NewWorker::on_addInsurance_clicked()
{
    bool result = openAddDocument("Страховка");
    if(result) {
        ui->addInsurance->hide();
    }
}


void NewWorker::on_AddRegestry_clicked()
{
    bool result = openAddDocument("Meldung AT");
    if(result) {
        ui->AddRegestry->hide();
    }
}


void NewWorker::on_AddA1_clicked()
{
    bool result = openAddDocument("A1-AT");
    if(result) {
        ui->AddRegestry->hide();
    }
}

void NewWorker::on_addEvent_clicked()
{
    Event* tempEvent = new Event();
    tempEvent->setBeginsOn(ui->CalendarWidget->getSelectedDate());
    NewEvent window(tempEvent);
    window.setModal(true);
    window.exec();

    if(tempEvent->getName().isEmpty()) {
        qDebug()<<"Event Was NOT created\n";
        delete tempEvent;
    }
    else {
        worker->addEvent(tempEvent);
        qDebug()<<tempEvent->toString();
        CustomListitem* Event = new CustomListitem(tempEvent->getName(), tempEvent->getID(), this);
        ui->Events->addItem(Event);
    }
    ui->CalendarWidget->setEvents(worker->getEvents());
    ui->CalendarWidget->setUpEvents();
}

void NewWorker::on_addSchedule_clicked()
{
    Schedule* tempSchedule = new Schedule();

    NewSchedule window(tempSchedule, worker->getSchedules(), facilities, this);
    window.setModal(true);
    window.exec();

    if(tempSchedule->getFacilityID() == -1) {
        qDebug()<<"Schedule Was NOT created\n";
        delete tempSchedule;
    }
    else {
        worker->addSchedule(tempSchedule);
        qDebug()<<tempSchedule->getID();
        CustomListitem* Schedule = new CustomListitem(tempSchedule->getBeginsOnDate().toString("dd/MM/yyyy") + " - " + tempSchedule->getEndsOnDate().toString("dd/MM/yyyy"), tempSchedule->getID(), this);;
        ui->Schedules->addItem(Schedule);
    }
}

void NewWorker::on_removeDocument_clicked()
{
    worker->removeDocument(ui->Documents->getSelectedItemID());
    ui->Documents->removeSelectedItem();
    ui->Documents->repaint();
}

void NewWorker::on_removeEvent_clicked()
{
    worker->removeEvent(ui->Events->getSelectedItemID());
    ui->Events->removeSelectedItem();
    ui->Events->repaint();

    ui->CalendarWidget->setEvents(worker->getEvents());
    ui->CalendarWidget->setUpEvents();
}

void NewWorker::on_removeSchedule_clicked()
{
    worker->removeSchedule(ui->Schedules->getSelectedItemID());
    ui->Schedules->removeSelectedItem();
    ui->Schedules->repaint();
}

void NewWorker::on_viewEvent_clicked()
{
    long long id = ui->Events->getSelectedItemID();
    qDebug() << ui->Events->getSelectedItemID();
    if(id != CustomListWidget::invalidID) {
        for(auto event : worker->getEvents()) {
            if(event->getID() == id) {
                ViewEvent window(event, this);
                window.setModal(true);
                window.exec();
            }
        }
    }
    else {
        qDebug() << "Something went wrong!";
    }
}

void NewWorker::on_viewSchedule_clicked()
{
    long long id = ui->Schedules->getSelectedItemID();
    if(id != CustomListWidget::invalidID) {
        for(auto schedule : worker->getSchedules()) {
            if(schedule->getID() == id) {
                ViewSchedule window(schedule, facilities, this);
                window.setModal(true);
                window.exec();
            }
        }
    }
    else {
        qDebug() << "Something went wrong!";
    }
}

void NewWorker::on_viewDocument_clicked()
{
    long long id = ui->Documents->getSelectedItemID();
    if(id != CustomListWidget::invalidID) {
        for(auto document : worker->getDocuments()) {
            if(document->getID() == id) {
                ViewDocument window(document, this);
                window.setModal(true);
                window.exec();
                break;
            }
        }
    }
    else {
        qDebug() << "Something went wrong!";
    }
}

NewWorker::~NewWorker()
{
    delete ui;
}

void NewWorker::on_RBSingle_clicked()
{
    worker->setStatus(MaritalStatus::single);
}

void NewWorker::on_RBMarried_clicked()
{
    worker->setStatus(MaritalStatus::married);
}

void NewWorker::on_RBDivorced_clicked()
{
    worker->setStatus(MaritalStatus::divorced);
}

void NewWorker::on_RBWidow_clicked()
{
    worker->setStatus(MaritalStatus::widow);
}

void NewWorker::on_RBMale_clicked()
{
    worker->setSex(Sex::male);
}

void NewWorker::on_RBFemale_clicked()
{
    worker->setSex(Sex::female);
}

void NewWorker::on_RB_ELID_clicked()
{
    worker->setFirm(Firm::ELID);
}

void NewWorker::on_RB_ELID_SP_clicked()
{
    worker->setFirm(Firm::ELID_SP);
}
