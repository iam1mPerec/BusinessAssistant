#include <QDebug>
#include <QPushButton>
#include <QDir>
#include <QDate>
#include <QCoreApplication>
#include "document.h"
#include "statics.h"

QString Document::mainPath = "documents";
long long Document::count = 0;

Document::Document(long long ParentID, QString ParentType) :
    parentType(ParentType),
    ExpirationDate(nullptr),
    path(""),
    parentID(ParentID),
    ID(++count),
    scansID(0)
{
    this->ExpirationDate = new QDate();
}

Document::Document(const Document &anotherDoc) :
    name(anotherDoc.name),
    parentType(anotherDoc.parentType),
    scans(anotherDoc.scans),
    path(anotherDoc.path),
    parentID(anotherDoc.parentID),
    ID(anotherDoc.ID),
    scansID(anotherDoc.scansID)

{
    ExpirationDate = new QDate(*anotherDoc.ExpirationDate);
}

Document::Document(long long ParentID, QString ParentType, long long PresetID, long long PresetScansID) :
    parentType(ParentType),
    ExpirationDate(nullptr),
    path(""),
    parentID(ParentID),
    ID(PresetID),
    scansID(PresetScansID)
{
    this->ExpirationDate = new QDate();
    if(count < ID) {
        count = ID;
    }
}

long long Document::getCount()
{
    return count;
}

void Document::setCount(long long value)
{
    count = value;
}

QString Document::getPath() const
{
    return path;
}

void Document::setPath(const QString &value)
{
    path = value;
}

long long Document::getScansID() const
{
    return scansID;
}

void Document::addScan(QString NewScan) {
    this->scans.push_back(NewScan);
}

void Document::removeScan(const QString &ScanToRemove) {
    qDebug("was removed\n");
    scans.removeOne(ScanToRemove);
}

void Document::copyScans(QList<QString> NewScans)
{
    for(auto scan : NewScans) {
        addScan(scan);
    }
}

void Document::deleteScans() {
    QDir dir(path);
    dir.removeRecursively();
    path.clear();
    scans.clear();
}

void Document::refactorScans(QList<QString> Scans) {
    if(path.isEmpty()) {
        createDirectory(mainPath);

        path = mainPath + "/" + parentType;
        createDirectory(path);

        QString DocType = "";
        if(parentType == "facilities")
        {
            DocType = "facility";
        }
        else if(parentType == "workers")
        {
            DocType = "worker";
        }
        else {
            qDebug("Something wierd happened in document.h in refactorScans() function");
        }
        path += "/" + DocType +"#" + QString::number(parentID);
        createDirectory(path);

        path += "/doc#" + QString::number(ID);
        createDirectory(path);
    }

    for(auto scan : Scans) {
        qDebug()<< "Scan:" <<scan;
        QString FilePath = path + "/" + name + "#" +  QString::number(++scansID) + getExstension(scan);
        qDebug()<< "Path:" <<FilePath;
        QFile::copy(scan, FilePath);
        scans.push_back(FilePath);
    }
}

void Document::deleteTemp()
{
    QDir dir("temp/");
    dir.removeRecursively();
}

QString Document::getExstension(QString path) const
{
    QString ext = "";
    for(int i = path.length() - 1; i > 0; --i) {
        ext.push_front(path[i]);
        if(path[i] == '.') {
            qDebug()<<ext;
            return ext;
        }
    }
    ext.clear();
    qDebug()<<ext;
    return ext;
}

void Document::setName(QString NewName) {
    this->name = NewName;
}

void Document::setDate(const QDate &NewDate) {
    ExpirationDate->setDate(NewDate.year(), NewDate.month(), NewDate.day());
}

QString Document::getName() const {
    return this->name;
}

QDate Document::getExpirationDate() const
{
    return *ExpirationDate;
}

long long Document::getID() const
{
    return ID;
}

QList<QString> Document::getScans() const
{
    return scans;
}

QList<QString> Document::copyTemp() const
{
    QList<QString> tempList;
    createDirectory("temp");
    int tempID = 0;

    for(auto scan : scans) {
        QString FilePath = "temp/file#" + QString::number(++tempID) + getExstension(scan);
        bool result = QFile::copy(scan, FilePath);
        qDebug()<<FilePath << result;
        tempList.push_back(FilePath);
    }
    return tempList;
}

void Document::resetScansID() {
    scansID = 0;
}

Document::~Document() {
    delete ExpirationDate;
    scans.clear();
}

QDataStream &operator <<(QDataStream &stream, const Document &document)
{
    stream<<document.getName();
    stream<<document.getExpirationDate();
    stream<<document.getPath();
    stream<<document.getScans().count();

    for(auto scan : document.getScans()) {
        stream<<scan;
    }
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Document &document)
{
    QString NAME;
    QString PATH;
    QDate   DATE;

    stream>>NAME;
    document.setName(NAME);

    stream>>DATE;
    document.setDate(DATE);

    stream>>PATH;
    document.setPath(PATH);

    int scansCount;
    stream>>scansCount;

    for(int i = 0; i < scansCount; i++) {
        QString SCAN_NAME;
        stream>>SCAN_NAME;
        document.addScan(SCAN_NAME);
    }
    return stream;
}

bool dateComp(Document *a, Document *b)
{
    return (a->getExpirationDate() > b->getExpirationDate());
}
