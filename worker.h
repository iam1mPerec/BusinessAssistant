#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <QList>
#include <QDate>
#include "EnumStates.h"
#include "EnumMaritalStatus.h"
#include "EnumSex.h"
#include "EnumFirm.h"

class Worker {

private:

    static long long count;

    QString surname;
    QString name;
    QString birthname;
    QDate   birthdate;
    QString placeOfBirth;
    QString citizenship;
    QString address;
    QString town;
    QString zip;
    QString phone;
    QString email;
    MaritalStatus status;
    Sex sex;
    Firm firm;



    QDate firedAt;

    QList<class Event*> events;
    QList<class Schedule*> schedules;
    QList<class Document*> documents;
    long long ID;

public:
    Worker();
    Worker(long long PresetID);

    void setName(const QString &newName);
    void setSurname(const QString &newName);
    void setBirthName(const QString &newName);
    void setAddress(const QString &NewAddress);
    void setTown(const QString &NewTown);
    void setZip(const QString &NewZip);
    void setPhone(const QString &newPhone);
    void setEmail(const QString Email);
    void setCitizenship(const QString Citizenship);
    void setBirthdate(const QDate &BirthDay);
    void setPlaceOfBirth(const QString PlaceOfBirth);
    void setFired(const QDate &FiredAt);
    void setStatus(const MaritalStatus Status);
    void setSex(const Sex Sex);
    void setFirm(const Firm Firm);
    void addDocument(class Document *NewDocument);
    void addEvent(class Event *NewEvent);
    void addSchedule(class Schedule *NewSchedule);
    void removeDocument(long long RemoveID);
    void removeAllDocuments();
    void removeEvent(long long RemoveID);
    void removeSchedule(long long RemoveID);

    QList<class Schedule*> getRelevantSchedules(int year, long long FacilityID) const;

    QString getName()       const;
    QString getSurName()    const;
    QString getBirthName()  const;
    QString getAddress()    const;
    QString getTown()       const;
    QString getZip()        const;
    QString getPhone()      const;
    QString getTitleString() const;
    QString getPlaceOfBirth() const;
    QString getCitizenship() const;
    QDate   getBirthDate()  const;
    QDate   getFiredAt()    const;
    QDate   getStartWorkOn()const;
    QDate   getEndWorkOn()  const;
    QString getEmail()      const;
    QString getFirmString() const;
    QString getStatusString() const;
    MaritalStatus getStatus() const;
    Sex getSex()            const;
    Firm getFirm()          const;
    QString getNameAndSurname() const;
    long long getID()       const;
    bool hasGender() const;
    bool hasFirm() const;
    bool hasStatus() const;
    bool isFired()          const;
    bool isAvailable(QDate BeginDate, QDate EndDate) const;
    bool isWorking(QDate Date, long long FacilityID) const;
    long long isWorking(QDate Date) const;
    QDate getClosestExpirationDate() const;

    state getState(QDate RequestedDate)          const;
    const QList<class Document*> &getDocuments() const;
    const QList<class Event*>    &getEvents()    const;
    const QList<class Schedule*> &getSchedules() const;

    ~Worker();
};

QDataStream &operator <<(QDataStream &stream, const Worker &myclass);
QDataStream &operator >>(QDataStream &stream, Worker &myclass);

#endif // WORKER_H
