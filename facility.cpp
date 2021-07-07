#include <QDir>
#include <QDataStream>
#include "facility.h"
#include "worker.h"
#include "document.h"

long long Facility::count = 0;

void Facility::setCount(int NewCount)
{
    count = NewCount;
}

long long Facility::getCount()
{
    return count;
}

void Facility::setTown(const QString &NewTown)
{
    town = NewTown;
}

void Facility::setZip(const QString &NewZip)
{
    zip = NewZip;
}

void Facility::setMaxWorkers(const int MaxWorkers)
{
    this->maxWorkers = MaxWorkers;
}

Facility::Facility():
    ID(++count),
    firm(Firm::none)
{
}

Facility::Facility(long long PresetID):
    ID(PresetID),
    firm(Firm::none)
{
    if(count < ID) {
        count = ID;
    }
}

void Facility::setOwner(const QString &NewOwner) {
    this->owner = NewOwner;
}
void Facility::setAddress(const QString &NewAddress) {
    this->address = NewAddress;
}
void Facility::setName(const QString &NewName)
{
    name = NewName;
}

void Facility::addDocument(Document *NewDocument)
{
    this->documents.push_back(NewDocument);
}

void Facility::removeDocument(long long RemoveID)
{
    for(auto item : documents) {
        if(item->getID() == RemoveID) {
            item->deleteScans();
            documents.removeOne(item);
            delete item;
        }
    }
}

void Facility::removeAllDocuments()
{
    for(auto item : documents) {
        item->deleteScans();
        documents.removeOne(item);
        delete item;
    }
    QDir dir("documents/facilities/facility #" + QString::number(ID));
    dir.removeRecursively();
}

QString Facility::getOwner() const {
    return this->owner;
}

QString Facility::getAddress() const {
    return this->address;
}

QString Facility::getName() const {
    return this->name;
}

QString Facility::getTown() const
{
    return this->town;
}

QString Facility::getZip() const
{
    return this->zip;
}

QString Facility::getFirmString() const
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

bool Facility::hasFirm() const
{
    return this->firm != Firm::none;
}

int Facility::getMaxWorkers() const
{
    return this->maxWorkers;
}

Firm Facility::getFirm() const
{
    return this->firm;
}

QDate Facility::getClosestExpirationDate() const
{
    if(!documents.isEmpty()) {
        Document * doc = *std::max_element(documents.begin(), documents.end(), dateComp);
        return doc->getExpirationDate();
    }
    else {
        return QDate();
    }
}

void Facility::setFirm(const Firm Firm)
{
    firm = Firm;
}

long long Facility::getID() const
{
    return this->ID;
}

const QList<Document*> &Facility::getDocuments() const
{
    return documents;
}

Facility::~Facility() {
    for(auto document : documents) {
        delete document;
    }
}

QDataStream &operator <<(QDataStream &stream, const Facility &facility)
{
    stream<<facility.getID();
    stream<<facility.getName();
    stream<<facility.getOwner();
    stream<<facility.getAddress();
    stream<<facility.getTown();
    stream<<facility.getZip();
    stream<<facility.getMaxWorkers();
    stream << int(facility.getFirm());
    stream<<facility.getDocuments().count();

    for(auto document : facility.getDocuments())
    {
        stream<<document->getID();
        stream<<document->getScansID();
        stream<<*document;
    }

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Facility &facility)
{
    long long ID;
    stream>>ID;
    facility.ID = ID;

    Facility::count = std::max(ID, Facility::count);

    QString NAME;
    stream>>NAME;
    facility.setName(NAME);

    QString OWNER;
    stream>>OWNER;
    facility.setOwner(OWNER);

    QString ADDRESS;
    stream>>ADDRESS;
    facility.setAddress(ADDRESS);

    QString TOWN;
    stream>>TOWN;
    facility.setTown(TOWN);

    QString ZIP;
    stream>>ZIP;
    facility.setZip(ZIP);

    int MAX_WORKERS;
    stream>>MAX_WORKERS;
    facility.setMaxWorkers(MAX_WORKERS);

    int FIRM;
    stream >> FIRM;
    facility.setFirm(Firm(FIRM));

    int DocCount;
    stream>>DocCount;

    for(int i = 0; i < DocCount; i++) {
        long long PresetID;
        long long PresetScansID;
        stream>>PresetID;
        stream>>PresetScansID;
        Document* document = new Document(facility.getID(), "facilities", PresetID, PresetScansID);
        stream>>*document;
        facility.addDocument(document);
    }

    return stream;
}
