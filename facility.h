#ifndef FACILITY_H
#define FACILITY_H

#include <QList>
#include <QDate>
#include <QString>
#include "EnumFirm.h"

class Facility {

private:
    QString name;
    QString owner;
    QString address;
    QString town;
    QString zip;
    int maxWorkers;
    QList<class Document*> documents;
    static long long count;
    long long ID;
    Firm firm;

public:
    Facility();
    Facility(long long PresetID);
    static void setCount(int NewCount);
    static long long getCount();

    void setName(const QString &value);
    void setOwner(const QString &NewOwner);
    void setAddress(const QString &NewAddress);
    void setTown(const QString &NewTown);
    void setZip(const QString &NewZip);
    void setMaxWorkers(const int MaxWorkers);
    void setFirm(const Firm Firm);
    void addDocument(class Document *NewDocument);
    void removeDocument(long long RemoveID);

    QString getName() const;
    QString getOwner()   const;
    QString getAddress() const;
    QString getTown() const;
    QString getZip() const;
    QString getFirmString() const;
    bool hasFirm() const;
    long long getID()    const;
    int getMaxWorkers() const;
    Firm getFirm()      const;
    const QList<class Document*> &getDocuments() const;

    QDate getClosestExpirationDate() const;

    ~Facility();
};

QDataStream &operator <<(QDataStream &stream, const Facility &myclass);
QDataStream &operator >>(QDataStream &stream, Facility &myclass);

#endif // FACILITY_H
