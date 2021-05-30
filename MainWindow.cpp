#include <QPushButton>
#include <QFileInfo>
#include <QDebug>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include "MainWindow.h"
#include "NewFacility.h"
#include "ViewFacility.h"
#include "CustomListWidget.h"
#include "CustomListitem.h"
#include "LinkedTablesObserver.h"
#include "facility.h"
#include "NewWorker.h"
#include "ViewWorker.h"
#include "worker.h"
#include "NewEvent.h"
#include "ViewEvent.h"
#include "event.h"
#include "statics.h"
#include "ViewPrint.h"
#include "ui_MainWindow.h"
#include "WorkerFormSelection.h"
#include "FacilityTable.h"
#include "Settings.h"
const QString MainWindow::savePath = "save";

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_safeToClose(true),
    m_events_backed(false),
    m_facilities_backed(false),
    m_workers_backed(false),
    linkedTablesObserver(nullptr)
{
    ui->setupUi(this);
    ui->canselFacilitiesSearch->hide();
    ui->canselWorkersSearch->hide();
    ui->canselEventsSearch->hide();
    ui->WorkersFired->hide();
    ui->FiredCountGroup->hide();

    ui->Facilities->setErgentToTop(false);
    ui->Events->setErgentToTop(false);

    linkedTablesObserver = new LinkedTablesObserver;
    linkedTablesObserver->addSubscriber(ui->Workers);
    linkedTablesObserver->addSubscriber(ui->WorkersOnVacation);
    linkedTablesObserver->addSubscriber(ui->WorkersFired);
    ui->Workers->addObserver(linkedTablesObserver);
    ui->WorkersOnVacation->addObserver(linkedTablesObserver);
    ui->WorkersFired->addObserver(linkedTablesObserver);

    createDirectory(savePath);
    createDirectory(savePath + "/backup");

    QFile facilitiesFile( choosePath("/facilities.txt", m_facilities_backed) );
    m_safeToClose = false;
    if(facilitiesFile.open(QIODevice::ReadOnly))
    {
        QDataStream out(&facilitiesFile);
        out.setVersion(QDataStream::Qt_5_9);
        QDateTime timestamp;
        out>>timestamp;
        int count;
        out>>count;

        for(int i = 0; i < count; i++) {
            long long ID;
            out>>ID;
            Facility *facility = new Facility(ID);
            out>>*facility;
            addFacility(facility);
        }

    }
    facilitiesFile.close();

    QFile workersFile( choosePath("/workers.txt", m_workers_backed) );
    if(workersFile.open(QIODevice::ReadOnly))
    {
        QDataStream out(&workersFile);
        out.setVersion(QDataStream::Qt_5_9);
        QDateTime timestamp;
        out>>timestamp;
        int count;
        out>>count;

        for(int i = 0; i < count; i++) {
            long long ID;
            out>>ID;
            Worker *worker = new Worker(ID);
            out>>*worker;
            addWorker(worker);
        }

    }
    workersFile.close();

    QFile eventsFile( choosePath("/events.txt", m_events_backed) );
    if(eventsFile.open(QIODevice::ReadOnly))
    {

        QDataStream out(&eventsFile);
        out.setVersion(QDataStream::Qt_5_9);
        QDateTime timestamp;
        out>>timestamp;
        int count;
        out>>count;

        for(int i = 0; i < count; i++) {
            long long ID;
            out>>ID;
            Event *event = new Event(ID);
            out>>*event;
            addPublicEvent(event);
        }

    }
    eventsFile.close();

    m_safeToClose = true;

    ui->CalendarWidget->setEvents(publicEvents);
    ui->CalendarWidget->addEvents(privateEvents);

    ui->CalendarWidget->subscribe(ui->Workers);
    ui->CalendarWidget->subscribe(this);
    ui->CalendarWidget->subscribe(ui->EventDisplayWidget);

    this->showMaximized();
    sortFacilities();
}

void MainWindow::removePrivateEvents(Worker * Worker) {
    for(auto event : Worker->getEvents()) {
        ui->Events->removeItemByID(event->getID());
        ui->CalendarWidget->removeEvent(event->getID());
        privateEvents.removeOne(event);
    }
}

void MainWindow::saveFacilities()
{
    m_safeToClose = false;
    QFile file;
    m_facilities_backed? file.setFileName(savePath + "/facilities.txt") : file.setFileName(savePath + "/backup/facilities.txt");
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_9);
        in<<QDateTime::currentDateTime();
        in << facilities.count();    
        for(auto facility : facilities) {
            in << facility->getID();
            in << *facility;
        }
        m_facilities_backed = !m_facilities_backed;
    }
    file.flush();
    file.close();
    m_safeToClose = true;
}

void MainWindow::saveWorkers()
{
    m_safeToClose = false;
    QFile file;
    m_workers_backed? file.setFileName(savePath + "/workers.txt") : file.setFileName(savePath + "/backup/workers.txt");
    if(file.open(QIODevice::WriteOnly)) {

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_9);
        in<<QDateTime::currentDateTime();
        in << workers.count();
        for(auto worker : workers) {
            in << worker->getID();
            in << *worker;
        }
        m_workers_backed = !m_workers_backed;
    }
    file.flush();
    file.close();
    m_safeToClose = true;
}

void MainWindow::saveEvents()
{
    m_safeToClose = false;
    QFile file;
    m_events_backed? file.setFileName(savePath + "/events.txt") : file.setFileName(savePath + "/backup/events.txt");
    if(file.open(QIODevice::WriteOnly)) {

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_9);
        in << QDateTime::currentDateTime();
        in << publicEvents.count();
        for(auto event : publicEvents) {
            in << event->getID();
            in << *event;
        }
        m_events_backed = !m_events_backed;
    }
    file.flush();
    file.close();
    m_safeToClose = true;
}

void MainWindow::addFacility(Facility *NewFacility)
{
    facilities.push_back(NewFacility);
    CustomListitem *newFacility = new CustomListitem(NewFacility->getName(), NewFacility->getID(), NewFacility->getClosestExpirationDate(), this);
    newFacility->compareWithDate(ui->CalendarWidget->getSelectedDate(), ui->Facilities->getErgentToTop());
    connect(newFacility, SIGNAL(doubleClicked(long long)), this, SLOT(onFacilityClicked(long long)));
    ui->Facilities->addItem(newFacility);
    ui->Facilities->sortByNameExpiration();
    ui->facilitiesCount->setText(QString::number(ui->Facilities->getVisibleItemsCount()));
}

void MainWindow::addWorker(Worker *NewWorker)
{
    workers.push_back(NewWorker);
    if(!NewWorker->isFired()) {
        addPrivateEvents(NewWorker);
    }
    CustomListitem *newWorkerItem = new CustomListitem(NewWorker->getSurName() + " " + NewWorker->getName(), NewWorker->getID(), NewWorker->getClosestExpirationDate(), this);
    newWorkerItem->compareWithDate(ui->CalendarWidget->getSelectedDate(), ui->Workers->getErgentToTop());
    ui->Workers->addItem(newWorkerItem);
    connect(newWorkerItem, SIGNAL(doubleClicked(long long)), this, SLOT(onWorkerClicked(long long)));
    sortSchedules();
}

void MainWindow::addPublicEvent(Event *NewEvent)
{
    publicEvents.push_back(NewEvent);
    ui->CalendarWidget->addEvent(NewEvent);;
    CustomListitem *newEvent = new CustomListitem(NewEvent->getName(), NewEvent->getID(), NewEvent->getNextDate(), this);
    connect(newEvent, SIGNAL(doubleClicked(long long)), this, SLOT(onEventClicked(long long)));
    ui->Events->addItem(newEvent);
    ui->eventCount->setText(QString::number(ui->Events->getVisibleItemsCount()));
    ui->Events->sortByExpiration();
}

QString MainWindow::choosePath(const QString Path, bool &backed) const {
    QString result = backed? Path + "/backup" : Path;
    backed = !backed;
    QDateTime timeStamp, timeStampBacked;
    bool timestampPresent = false, timestampBackupPresent = false;

    QFile file(savePath + Path);
    if(file.open(QIODevice::ReadOnly)) {
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_9);
        out>>timeStamp;
        timestampPresent = true;
    }
    else {
        QMessageBox msgBox;
        QString msg = "Данные в " + Path + " были повреждены. Обратитесь к Разработчику";
        msgBox.setText(msg);
        msgBox.exec();
    }

    QFile fileBackup(savePath + "/backup" + Path);
    if(fileBackup.open(QIODevice::ReadOnly)) {
        QDataStream out(&fileBackup);
        out.setVersion(QDataStream::Qt_5_9);
        out>>timeStampBacked;
        timestampBackupPresent = true;
    }
    else {
        QMessageBox msgBox;
        QString msg = "Данные в " + Path + "/backup были повреждены. Обратитесь к Разработчику";
        msgBox.setText(msg);
        msgBox.exec();
    }

    file.close();
    fileBackup.close();

    if((timestampPresent && !timestampBackupPresent) || timeStamp > timeStampBacked) {
        backed = false;
        return savePath + Path;
    }
    else if((!timestampPresent && timestampBackupPresent) || timeStamp < timeStampBacked) {
        backed = true;
        return savePath + "/backup" +Path;
    }
    else return "";
}

void MainWindow::addPrivateEvents(Worker * Worker) {
    for(auto event : Worker->getEvents()) {
        if(!ui->Events->containsID(event->getID())) {
            CustomListitem* newEvent = new CustomListitem(event->getName(), event->getID(), event->getNextDate(), this);
            connect(newEvent, SIGNAL(doubleClicked(long long)), this, SLOT(onEventClicked(long long)));
            ui->Events->addItem(newEvent);
            ui->CalendarWidget->addEvent(event);
            privateEvents.append(event);
        }
    }
    ui->eventCount->setText(QString::number(ui->Events->getVisibleItemsCount()));
    ui->Events->sortByExpiration();
}

void MainWindow::sortSchedules()
{
    CustomListitem * selectedWorker;
    for(auto worker : workers) {
        selectedWorker = ui->Workers->extractItem(worker->getID());
        if(!selectedWorker) {
            selectedWorker = ui->WorkersOnVacation->extractItem(worker->getID());
        }
        if(!selectedWorker) {
            selectedWorker = ui->WorkersFired->extractItem(worker->getID());
        }

        if(selectedWorker) {
            switch(worker->getState(ui->CalendarWidget->getSelectedDate())) {
            case state::working:
                ui->Workers->addItem(selectedWorker);
                break;
            case state::fiered:
                ui->WorkersFired->addItem(selectedWorker);
                break;
            default:
                ui->WorkersOnVacation->addItem(selectedWorker);
                break;
            }
        }
    }
    ui->Workers->sortByNameExpiration();
    ui->WorkersOnVacation->sortByNameExpiration();
    ui->WorkersFired->sortByName();

    ui->workingCount->setText(QString::number(ui->Workers->getVisibleItemsCount()));
    ui->restingCount->setText(QString::number(ui->WorkersOnVacation->getVisibleItemsCount()));
    ui->firedCount->setText(QString::number(ui->WorkersFired->getVisibleItemsCount()));
}

void MainWindow::checkWorkersOnFirm()
{
    Firm firm = Firm::none;

    if(ui->sortWorkersELID->isChecked()) {
        firm = Firm::ELID_SP;
        this->hideWorkers(firm);
    }
    else if(ui->sortWorkersELID_SP->isChecked()) {
        firm = Firm::ELID;
        this->hideWorkers(firm);
    }
}

void MainWindow::checkFacilitiesOnFirm()
{
    Firm firm = Firm::none;

    if(ui->sortFacilitiesELID->isChecked()) {
        firm = Firm::ELID_SP;
        this->hideFacilities(firm);
    }
    else if(ui->sortFacilitiesELID_SP->isChecked()) {
        firm = Firm::ELID;
        this->hideFacilities(firm);
    }
}

void MainWindow::hideWorkers(Firm firm)
{
    for(auto worker : workers) {
        if(worker->getFirm() == firm) {
            CustomListitem* workerListItem = ui->Workers->getElementById(worker->getID());
            if(!workerListItem) {
                workerListItem = ui->WorkersOnVacation->getElementById(worker->getID());
            }
            if(!workerListItem) {
                workerListItem = ui->WorkersFired->getElementById(worker->getID());
            }
            if(workerListItem) {
                workerListItem->hide();
            }
        }
    }
}

void MainWindow::searchWorkersByFirm(Firm firm)
{
    ui->Workers->revealItems();
    ui->WorkersOnVacation->revealItems();
    ui->WorkersFired->revealItems();
    bool isSearching = !ui->canselWorkersSearch->isHidden();
    if(isSearching) {
        ui->Workers->hideUnrequestedItems(ui->workersKey->text());
        ui->WorkersOnVacation->hideUnrequestedItems(ui->workersKey->text());
        ui->WorkersFired->hideUnrequestedItems(ui->workersKey->text());
    }
    switch (firm) {
        case Firm::none:
            break;
        default:
            hideWorkers(firm);
            break;
    }
}

void MainWindow::hideFacilities(Firm firm)
{
    for(auto facility : facilities) {
        if(facility->getFirm() == firm) {
            CustomListitem* facilityListItem = ui->Facilities->getElementById(facility->getID());
            if(facilityListItem) {
                facilityListItem->hide();
            }
        }
    }
}

void MainWindow::searchFacilitiesByFirm(Firm firm)
{
    ui->Facilities->revealItems();
    bool isSearching = !ui->canselFacilitiesSearch->isHidden();
    if(isSearching) {
         ui->Facilities->hideUnrequestedItems(ui->facilitiesKey->text());
    }
    switch (firm) {
        case Firm::none:
            break;
        default:
            hideFacilities(firm);
            break;
    }
}

void MainWindow::sortFacilities()
{
    QMap<long long, int> involvedFacilities;
    QMap<long long, Facility*> Facilities;
    for(auto facility : facilities) {
        Facilities.insert(facility->getID(), facility);
    }
    for(auto worker : workers) {
        long long occupiedFacilityID = worker->isWorking(ui->CalendarWidget->getSelectedDate());
        if(occupiedFacilityID != -1) {
            if(!involvedFacilities.contains(occupiedFacilityID)) {
                involvedFacilities.insert(occupiedFacilityID, 1);
            } else {
                involvedFacilities[occupiedFacilityID] = involvedFacilities[occupiedFacilityID] + 1;
            }
        }
    }
    QMapIterator<long long, int> i(involvedFacilities);
    while (i.hasNext()) {
        i.next();
        expiration status = expiration::highlighted;
        if(Facilities[i.key()]->getMaxWorkers() == 0) {
            status = expiration::normal;
        }
        if(Facilities[i.key()]->getMaxWorkers() <= i.value()) {
            status = expiration::irrelevant;
        }
        ui->Facilities->getElementById(i.key())->setExp(status);
    }
    ui->Facilities->sortByNameExpiration();
}

void MainWindow::onDateSelected()
{
    ui->Facilities->revealItems();
    ui->canselFacilitiesSearch->hide();
    ui->sortFacilitiesELID->setChecked(false);
    ui->sortFacilitiesELID_SP->setChecked(false);

    ui->Workers->revealItems();
    ui->canselWorkersSearch->hide();
    ui->sortWorkersELID->setChecked(false);
    ui->sortWorkersELID_SP->setChecked(false);

    ui->Events->revealItems();
    ui->canselEventsSearch->hide();

    sortSchedules();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(m_safeToClose) {
        event->accept();
    } else {
        event->ignore();
        QMessageBox msgBox;
        msgBox.setText("Данные сохраняются. Пожалуйста не закрывайте программу");
        msgBox.exec();
    }
}

void MainWindow::onWorkerClicked(long long ID)
{
    viewWorker(ID);
}

void MainWindow::onFacilityClicked(long long ID)
{
    viewFacility(ID);
}

void MainWindow::onEventClicked(long long ID)
{
    viewEvent(ID);
}

void MainWindow::on_addFacility_clicked()
{
    Facility* facility = new Facility;
    NewFacility window(facility, this);

    window.setModal(true);
    window.exec();

    if(facility->getAddress().isEmpty()) {
        delete facility;
    }
    else {
        addFacility(facility);
        saveFacilities();
    }
}

void MainWindow::on_addWorker_clicked()
{
    Worker* worker = new Worker;
    NewWorker window(worker, facilities, this);
    window.setModal(true);
    window.exec();

    if(worker->getName().isEmpty()) {
        delete worker;
    }
    else {
        addWorker(worker);
        saveWorkers();
    }
}

void MainWindow::on_addEvent_clicked()
{
    Event* event = new Event;
    NewEvent window(event, this);
    window.setModal(true);
    window.exec();

    if(event->getName().isEmpty()) {
        delete event;
    }
    else {
        addPublicEvent(event);
        saveEvents();
    }
}

void MainWindow::on_removeFacility_clicked()
{
    long long id = ui->Facilities->getSelectedItemID();

    if(id == CustomListWidget::invalidID) {
        return;
    }

    for(auto facility : facilities) {
        if(facility->getID() == id) {
            facilities.removeOne(facility);
            facility->removeAllDocuments();
            delete facility;
        }
    }
    ui->Facilities->removeSelectedItem();
    saveFacilities();
    ui->Facilities->repaint();
    ui->facilitiesCount->setText(QString::number(ui->Facilities->getVisibleItemsCount()));
}

void MainWindow::on_removeWorker_clicked()
{   
    long long id = ui->Workers->getSelectedItemID();

    if(id == CustomListWidget::invalidID) {
        id = ui->WorkersOnVacation->getSelectedItemID();
    }
    else {
        ui->Workers->removeSelectedItem();
        ui->workingCount->setText(QString::number(ui->Workers->getVisibleItemsCount()));
    }

    if(id == CustomListWidget::invalidID) {
        id = ui->WorkersFired->getSelectedItemID();
    }
    else {
        ui->WorkersOnVacation->removeSelectedItem();
        ui->restingCount->setText(QString::number(ui->WorkersOnVacation->getVisibleItemsCount()));
    }

    //      nothing is selected
    if(id == CustomListWidget::invalidID) {
        return;
    }
    else {
        ui->WorkersFired->removeSelectedItem();
        ui->firedCount->setText(QString::number(ui->WorkersFired->getVisibleItemsCount()));
    }

    for(auto worker : workers) {
        if(worker->getID() == id) {
            worker->removeAllDocuments();
            removePrivateEvents(worker);
            workers.removeOne(worker);
            delete worker;
        }
    }
    saveWorkers();
    ui->eventCount->setText(QString::number(ui->Events->getVisibleItemsCount()));
    ui->Workers->repaint();
}

void MainWindow::on_removeEvent_clicked()
{
    long long id = ui->Events->getSelectedItemID();

    if(id == CustomListWidget::invalidID) {
        return;
    }

    for(auto event : publicEvents) {
        if(event->getID() == id) {
            publicEvents.removeOne(event);
            saveEvents();
            delete event;
        }
    }
    for(int i = 0; i < privateEvents.count(); i++) {
        if(privateEvents[i]->getID() == id) {
            for(auto worker : workers){
                worker->removeEvent(id);
            }
            privateEvents.removeAt(i);
            saveWorkers();
        }
    }
    ui->CalendarWidget->removeEvent(id);
    ui->Events->removeSelectedItem();
    ui->eventCount->setText(QString::number(ui->Events->getVisibleItemsCount()));
    ui->Events->repaint();
}

void MainWindow::viewFacility(long long ID) {
    if(ID != CustomListWidget::invalidID) {
        for(auto facility : facilities) {
            if(facility->getID() == ID) {
                ViewFacility window(facility, workers, this);
                window.setModal(true);
                window.exec();
                ui->Facilities->changeItemName(ID, facility->getName());
                ui->Facilities->changeItemExpDate(ID, facility->getClosestExpirationDate());
                ui->Facilities->sortByNameExpiration();
                saveFacilities();
            }
        }
    }
    else {
        qDebug() << "Something went wrong!";
    }
}

void MainWindow::on_viewFacility_clicked()
{
    long long id = ui->Facilities->getSelectedItemID();

    viewFacility(id);
}

void MainWindow::viewWorker(long long ID)
{
    if(ID != CustomListWidget::invalidID) {
        for(auto worker : workers) {
            if(worker->getID() == ID) {
                removePrivateEvents(worker);
                ViewWorker window(worker, facilities, this);
                window.setModal(true);
                window.exec();
                if(!worker->isFired()) {
                    addPrivateEvents(worker);
                }
                ui->Workers->changeItemName(ID, worker->getSurName() + " " + worker->getName());
                ui->Workers->changeItemExpDate(ID, worker->getClosestExpirationDate());
                ui->Workers->compareWithDate(ui->CalendarWidget->getSelectedDate());

                ui->WorkersOnVacation->changeItemName(ID, worker->getSurName() + " " + worker->getName());
                ui->WorkersOnVacation->changeItemExpDate(ID, worker->getClosestExpirationDate());
                ui->WorkersOnVacation->compareWithDate(ui->CalendarWidget->getSelectedDate());

                sortSchedules();
                saveWorkers();
            }
        }
    }
    else {
        qDebug() << "Something went wrong!";
    }
}

void MainWindow::on_viewWorker_clicked()
{
    long long id = ui->Workers->getSelectedItemID();

    if(id == CustomListWidget::invalidID) {
        id = ui->WorkersOnVacation->getSelectedItemID();
    }

    if(id == CustomListWidget::invalidID) {
        id = ui->WorkersFired->getSelectedItemID();
    }

    viewWorker(id);
}

void MainWindow::viewEvent(long long ID)
{
    if(ID != CustomListWidget::invalidID) {
        Event* viewedEvent = nullptr;
        for(auto event : publicEvents) {
            if(event->getID() == ID) {
                viewedEvent = event;
            }
        }
        if(!viewedEvent) {
            for(auto event : privateEvents) {
                if(event->getID() == ID) {
                    viewedEvent = event;
                }
            }
        }

        ViewEvent window(viewedEvent, this);
        window.setModal(true);
        window.exec();
        for(auto event : ui->Events->getItems()) {
            if(event->getID() == ID) {
                event->setLabelText(viewedEvent->getName());
                event->setExpDate(viewedEvent->getNextDate(), ui->Events->getErgentToTop());
            }
        }
        ui->Events->changeItemName(ID, viewedEvent->getName());
        ui->Events->sortByExpiration();
        ui->CalendarWidget->setUpEvents();
        saveEvents();
    }
    else {
        qDebug() << "Something went wrong!";
    }
}

void MainWindow::on_viewEvent_clicked()
{
    long long id = ui->Events->getSelectedItemID();
    viewEvent(id);
}

void MainWindow::on_searchFacilities_clicked()
{
    bool result = ui->Facilities->hideUnrequestedItems(ui->facilitiesKey->text());
    if(result) {
        ui->canselFacilitiesSearch->setHidden(false);
    }

    if(result) {
        checkFacilitiesOnFirm();
    }
    ui->facilitiesCount->setText(QString::number(ui->Facilities->getVisibleItemsCount()));
}

void MainWindow::on_searchWorkers_clicked()
{
    bool result = ui->Workers->hideUnrequestedItems(ui->workersKey->text());
    result = ui->WorkersOnVacation->hideUnrequestedItems(ui->workersKey->text());
    result = ui->WorkersFired->hideUnrequestedItems(ui->workersKey->text());
    if(result) {
        ui->canselWorkersSearch->setHidden(false);
    }

    if(result) {
        checkWorkersOnFirm();
    }
    ui->workingCount->setText(QString::number(ui->Workers->getVisibleItemsCount()));
    ui->restingCount->setText(QString::number(ui->WorkersOnVacation->getVisibleItemsCount()));
    ui->firedCount->setText(QString::number(ui->WorkersFired->getVisibleItemsCount()));
}

void MainWindow::on_searchEvents_clicked()
{
    bool result = ui->Events->hideUnrequestedItems(ui->eventsKey->text());
    if(result) {
        ui->canselEventsSearch->setHidden(false);
    }
    ui->eventCount->setText(QString::number(ui->Events->getVisibleItemsCount()));
}

void MainWindow::on_canselFacilitiesSearch_clicked()
{
    ui->Facilities->revealItems();
    ui->canselFacilitiesSearch->hide();
    ui->facilitiesKey->clear();

    this->checkFacilitiesOnFirm();
    ui->facilitiesCount->setText(QString::number(ui->Facilities->getVisibleItemsCount()));
}

void MainWindow::on_canselWorkersSearch_clicked()
{
    ui->Workers->revealItems();
    ui->WorkersOnVacation->revealItems();
    ui->WorkersFired->revealItems();

    ui->canselWorkersSearch->hide();
    ui->workersKey->clear();

    this->checkWorkersOnFirm();

    ui->workingCount->setText(QString::number(ui->Workers->getVisibleItemsCount()));
    ui->restingCount->setText(QString::number(ui->WorkersOnVacation->getVisibleItemsCount()));
    ui->firedCount->setText(QString::number(ui->WorkersFired->getVisibleItemsCount()));
}

void MainWindow::on_canselEventsSearch_clicked()
{
    ui->Events->revealItems();
    ui->canselEventsSearch->hide();
    ui->eventsKey->clear();
    ui->eventCount->setText(QString::number(ui->Events->getVisibleItemsCount()));
}

MainWindow::~MainWindow()
{
    delete linkedTablesObserver;
    for(auto facility : facilities) {
        delete facility;
    }
    for(auto worker : workers) {
        delete worker;
    }
    for(auto event : publicEvents) {
        delete event;
    }
    delete ui;
}

void MainWindow::on_ShowFiredCheckBox_stateChanged(int state)
{
    switch (state) {
    case Qt::Unchecked:
        ui->WorkersFired->setHidden(true);
        ui->FiredCountGroup->setHidden(true);
        break;
    default:
        ui->WorkersFired->setHidden(false);
        ui->FiredCountGroup->setHidden(false);
        break;
    }
}

void MainWindow::on_viewWorkerForms_clicked()
{
    long long id = ui->Workers->getSelectedItemID();

    if(id == CustomListWidget::invalidID) {
        id = ui->WorkersOnVacation->getSelectedItemID();
    }

    if(id == CustomListWidget::invalidID) {
        id = ui->WorkersFired->getSelectedItemID();
    }

    Worker* selectedWorker = nullptr;
    for(auto worker : workers) {
        if(worker->getID() == id) {
            selectedWorker = worker;
        }
    }
    QStringList facilityNames;
    for(auto facility : facilities) {
        facilityNames.append(facility->getName());
    }
    if(selectedWorker) {
        WorkerFormSelection window(facilityNames, selectedWorker, this);
        window.setModal(true);
        window.exec();
        Settings::removeInstance();
    }
}

void MainWindow::on_tableFacility_clicked()
{
    long long id = ui->Facilities->getSelectedItemID();
    Facility* selectedFacility = nullptr;
    for(auto facility : this->facilities) {
        if(facility->getID() == id) {
            selectedFacility = facility;
        }
    }
    if(selectedFacility) {
        FacilityTable window(selectedFacility, this->workers, QDate::currentDate().year(), this);
        window.setModal(true);
        window.showMaximized();
        window.exec();
    }
}

void MainWindow::on_sortWorkersELID_SP_clicked()
{
    ui->sortWorkersELID->setChecked(false);

    if(ui->sortWorkersELID_SP->isChecked()) {
        this->searchWorkersByFirm(Firm::ELID);
    }
    else {
        this->searchWorkersByFirm(Firm::none);
    }

    ui->workingCount->setText(QString::number(ui->Workers->getVisibleItemsCount()));
    ui->restingCount->setText(QString::number(ui->WorkersOnVacation->getVisibleItemsCount()));
    ui->firedCount->setText(QString::number(ui->WorkersFired->getVisibleItemsCount()));
}

void MainWindow::on_sortWorkersELID_clicked()
{
    ui->sortWorkersELID_SP->setChecked(false);
    if(ui->sortWorkersELID->isChecked()) {
        this->searchWorkersByFirm(Firm::ELID_SP);
    }
    else {
        this->searchWorkersByFirm(Firm::none);
    }

    ui->workingCount->setText(QString::number(ui->Workers->getVisibleItemsCount()));
    ui->restingCount->setText(QString::number(ui->WorkersOnVacation->getVisibleItemsCount()));
    ui->firedCount->setText(QString::number(ui->WorkersFired->getVisibleItemsCount()));
}

void MainWindow::on_sortFacilitiesELID_clicked()
{
    ui->sortFacilitiesELID_SP->setChecked(false);
    if(ui->sortFacilitiesELID->isChecked()) {
        this->searchFacilitiesByFirm(Firm::ELID_SP);
    }
    else {
        this->searchFacilitiesByFirm(Firm::none);
    }

    ui->facilitiesCount->setText(QString::number(ui->Facilities->getVisibleItemsCount()));
}

void MainWindow::on_sortFacilitiesELID_SP_clicked()
{
    ui->sortFacilitiesELID->setChecked(false);
    if(ui->sortFacilitiesELID_SP->isChecked()) {
        this->searchFacilitiesByFirm(Firm::ELID);
    }
    else {
        this->searchFacilitiesByFirm(Firm::none);
    }

    ui->facilitiesCount->setText(QString::number(ui->Facilities->getVisibleItemsCount()));
}
