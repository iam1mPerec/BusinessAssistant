#include <QDir>
#include <QDataStream>
#include "event.h"
#include "document.h"
#include "schedule.h"
#include "worker.h"

long long Worker::count = 0;

Worker::Worker():
    status(MaritalStatus::none),
    sex(Sex::none),
    firm(Firm::none),
    ID(++count)
{
}

Worker::Worker(long long presetID) :
    surname(""),
    name(""),
    birthname(""),
    placeOfBirth(""),
    citizenship(""),
    address(""),
    town(""),
    zip(""),
    phone(""),
    email(""),
    status(MaritalStatus::none),
    sex(Sex::none),
    firm(Firm::none),
    ID(presetID)
{
    if(count < ID) {
        count = ID;
    }
}

QDate Worker::getClosestExpirationDate() const
{
    if(!documents.isEmpty()) {
        Document * doc = *std::max_element(documents.begin(), documents.end(), dateComp);
        return doc->getExpirationDate();
    }
    else {
        return QDate();
    }
}

void Worker::setName(const QString &newName)
{
    name = newName;
}

void Worker::setSurname(const QString &newSurname)
{
    surname = newSurname;
}

void Worker::setBirthName(const QString &newMiddleName)
{
    birthname = newMiddleName;
}

void Worker::setAddress(const QString &NewAddress)
{
    address = NewAddress;
}

void Worker::setTown(const QString &NewTown)
{
    town = NewTown;
}

void Worker::setZip(const QString &NewZip)
{
    zip = NewZip;
}


void Worker::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

void Worker::setEmail(const QString Email)
{
    email = Email;
}

void Worker::setCitizenship(const QString Citizenship)
{
    citizenship = Citizenship;
}

void Worker::setBirthdate(const QDate &value)
{
    birthdate = value;
}

void Worker::setPlaceOfBirth(const QString PlaceOfBirth)
{
    placeOfBirth = PlaceOfBirth;
}

void Worker::setFired(const QDate &FiredAt)
{
    firedAt = FiredAt;
}

void Worker::setStatus(const MaritalStatus Status)
{
    status = Status;
}

void Worker::setSex(const Sex Sex)
{
    sex = Sex;
}

void Worker::setFirm(const Firm Firm)
{
    firm = Firm;
}

void Worker::addDocument(Document *NewDocument)
{
    documents.push_back(NewDocument);
}

void Worker::addEvent(Event *NewEvent)
{
    events.push_back(NewEvent);
}

void Worker::addSchedule(Schedule *NewSchedule)
{
    schedules.push_back(NewSchedule);
}

void Worker::removeDocument(long long RemoveID)
{
    for(auto item : documents) {
        if(item->getID() == RemoveID) {
            item->deleteScans();
            documents.removeOne(item);
        }
    }
}

void Worker::removeAllDocuments()
{
    for(auto item : documents) {
        item->deleteScans();
        documents.removeOne(item);
    }
    QDir dir("documents/workers/worker #" + QString::number(ID));
    dir.removeRecursively();
}

void Worker::removeEvent(long long RemoveID)
{
    for(auto item : events) {
        if(item->getID() == RemoveID) {
            events.removeOne(item);
        }
    }
}

void Worker::removeSchedule(long long RemoveID)
{
    for(auto item : schedules) {
        if(item->getID() == RemoveID) {
            schedules.removeOne(item);
        }
    }
}

QString Worker::getName() const
{
    return name;
}

QString Worker::getSurName() const
{
    return surname;
}

QString Worker::getBirthName() const
{
    return birthname;
}

QString Worker::getAddress() const
{
    return address;
}

QString Worker::getTown() const
{
    return town;
}

QString Worker::getZip() const
{
    return zip;
}

QString Worker::getPhone() const
{
    return phone;
}

QString Worker::getTitleString() const
{
    switch (this->sex) {
        case Sex::male:
        return "Herr";
        case Sex::female:
        return "Frau";
        default:
        return "None";
    }
}

QString Worker::getNameAndSurname() const {
    return name + " " + surname;
}

QDate Worker::getBirthDate() const
{
    return birthdate;
}

QDate Worker::getFiredAt() const
{
    return firedAt;
}

QString Worker::getEmail() const
{
    return email;
}

QString Worker::getFirmString() const
{
    switch (this->firm) {
        case Firm::ELID:
        return "ELID";
        case Firm::ELID_SP:
        return "ELID-SP";
        default:
        return "NONE";
    }
}

QString Worker::getStatusString() const
{
    switch(this->status) {
        case MaritalStatus::single:
            return "Ledig";
        case MaritalStatus::married:
            return "Verheiratet";
        case MaritalStatus::divorced:
            return "Geschieden";
        case MaritalStatus::widow:
            return "witwe";
        default:
            return "Undefined";
    }
}

QString Worker::getPlaceOfBirth() const
{
    return placeOfBirth;
}

QString Worker::getCitizenship() const
{
    return citizenship;
}

MaritalStatus Worker::getStatus() const
{
    return status;
}

Sex Worker::getSex() const
{
    return sex;
}

Firm Worker::getFirm() const
{
    return firm;
}

long long Worker::getID() const
{
    return ID;
}

bool Worker::hasGender() const
{
    return this->sex != Sex::none;
}

bool Worker::hasFirm() const
{
    return this->firm != Firm::none;
}

bool Worker::hasStatus() const
{
    return this->status != MaritalStatus::none;
}

bool Worker::isFired() const
{
    return firedAt.isValid();
}

bool Worker::isWorking(QDate Date, long long FacilityID) const
{
    if(isFired() && Date >= firedAt) {
        return false;
    }

    for(auto schedule : schedules) {
        if(schedule->getFacilityID() == FacilityID && schedule->isRelevant(Date) == DateTypes::work) {
            return true;
        }
    }
    return false;
}

long long Worker::isWorking(QDate Date) const
{
    if(isFired() && Date >= firedAt) {
        return -1;
    }

    for(auto schedule : schedules) {
        if(schedule->isRelevant(Date) == DateTypes::work) {
            return schedule->getFacilityID();
        }
    }
    return -1;
}

bool Worker::isAvailable(QDate BeginDate, QDate EndDate) const
{
//    check if worker is fired during this period
    if(isFired()) {
        if(firedAt >= BeginDate && firedAt <= EndDate) {
            return false;
        }
    }

    for(auto schedule : schedules) {
        QDate WorkBeginsOn = schedule->getBeginsOnDate();
        QDate WorkEndsOn = schedule->getEndsOnDate();

        if(BeginDate > WorkEndsOn || WorkBeginsOn > EndDate) {
            return false;
        }
    }

    return true;
}

state Worker::getState(QDate RequestedDate) const
{
//    we check if the worker was fired
    if(isFired() && RequestedDate >= firedAt) {
        return state::fiered;
    }

    for(auto schedule : schedules) {
        if(schedule->isRelevant(RequestedDate) != DateTypes::none) {
            if(schedule->isRelevant(RequestedDate) == DateTypes::rest) {
                return state::resting;
            }
            else {
                return state::working;
            }
        }
    }
//    if has no state
    return state::empty;
}

QList<Schedule*> Worker::getRelevantSchedules(int year, long long FacilityID) const {
    QList<Schedule*> RelevantSchedules;

    for(auto schedule : schedules) {

        if(schedule->getFacilityID() == FacilityID && ( schedule->getBeginsOnDate().year() <= year && schedule->getEndsOnDate().year() >= year) ) {
            RelevantSchedules.push_back(schedule);
        }
    }

    return RelevantSchedules;
}


const QList<Document*> &Worker::getDocuments() const
{
    return documents;
}

const QList<Event *> &Worker::getEvents() const
{
    return events;
}

const QList<Schedule *> &Worker::getSchedules() const
{
    return schedules;
}

Worker::~Worker()
{
    for(auto event : events) {
        delete event;
    }

    for(auto document : documents) {
        delete document;
    }

    for(auto schedule : schedules) {
        delete  schedule;
    }
}

QDataStream &operator <<(QDataStream &stream, const Worker &worker)
{
    stream << worker.getName();
    stream << worker.getSurName();
    stream << worker.getBirthName();
    stream << worker.getAddress();
    stream << worker.getTown();
    stream << worker.getZip();
    stream << worker.getPhone();
    stream << worker.getBirthDate();
    stream << worker.getFiredAt();
    stream << worker.getPlaceOfBirth();
    stream << worker.getCitizenship();
    stream << worker.getEmail();
    stream << int(worker.getStatus());
    stream << int(worker.getSex());
    stream << int(worker.getFirm());

    stream << worker.getDocuments().count();
    for(auto document : worker.getDocuments()) {
        stream << document->getID();
        stream << document->getScansID();
        stream << *document;
    }

    stream << worker.getEvents().count();
    for(auto event : worker.getEvents()) {
        stream << event->getID();
        stream << *event;
    }

    stream << worker.getSchedules().count();
    for(auto schedule : worker.getSchedules()) {
        stream << schedule->getID();
        stream << *schedule;
    }

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Worker &worker)
{
    QString TempString;
    QDate   TempDate;

    stream >> TempString;
    worker.setName(TempString);

    stream >> TempString;
    worker.setSurname(TempString);

    stream >> TempString;
    worker.setBirthName(TempString);

    stream >> TempString;
    worker.setAddress(TempString);

    stream >> TempString;
    worker.setTown(TempString);

    stream >> TempString;
    worker.setZip(TempString);

    stream >> TempString;
    worker.setPhone(TempString);

    stream >> TempDate;
    worker.setBirthdate(TempDate);

    stream >> TempDate;
    worker.setFired(TempDate);

    stream >> TempString;
    worker.setPlaceOfBirth(TempString);

    stream >> TempString;
    worker.setCitizenship(TempString);

    stream >> TempString;
    worker.setEmail(TempString);

    int TempStatus;
    stream >> TempStatus;
    worker.setStatus(MaritalStatus(TempStatus));

    int TempSex;
    stream >> TempSex;
    worker.setSex(Sex(TempSex));

    int TempFirm;
    stream >> TempFirm;
    worker.setFirm(Firm(TempFirm));

    int DocCount;
    stream>>DocCount;
    for(int i = 0; i < DocCount; i++) {
        long long PresetID;
        long long PresetScansID;
        stream >> PresetID;
        stream >> PresetScansID;
        Document *document = new Document(worker.getID(), "workers", PresetID, PresetScansID);
        stream >> *document;
        worker.addDocument(document);
    }

    int EventCount;
    stream>>EventCount;
    for(int i = 0; i < EventCount; i++) {
        long long PresetID;
        stream >> PresetID;
        Event *event = new Event(PresetID);
        stream >> *event;
        worker.addEvent(event);
    }

    int ScheduleCount;
    stream>>ScheduleCount;
    for(int i = 0; i < ScheduleCount; i++) {
        long long PresetID;
        stream >> PresetID;
        Schedule *schedule = new Schedule(PresetID);
        stream >> *schedule;
        worker.addSchedule(schedule);
    }

    return stream;
}
