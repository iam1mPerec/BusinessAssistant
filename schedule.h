#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QString>
#include <QDate>
#include "EnumDateType.h"
#include "period.h"

class Schedule
{
    static long long count;

    long long ID;

    Period period;

    int workDays;
    int restDays;

    long long facilityID;

public:
    Schedule();
    Schedule(long long PresetID);

    long long getID()           const;
    int getWorkDays()           const;
    int getRestDays()           const;
    QDate getBeginsOnDate()     const;
    QDate getEndsOnDate()       const;
    long long getFacilityID()   const;
    Period getPeriod() const;
    bool intersects(const Period period) const;
    DateTypes isRelevant(QDate Date, QDate FiredAt) const;
    DateTypes isRelevant(QDate Date) const;

    void setWorkDays(int WorkDays);
    void setRestDays(int RestDays);
    void setBeginsOn(const QDate &StarWorkOn);
    void setEndsOn(const QDate &EndsOn);

    void setFacilityID(long long NewFacilityID);
};

QDataStream &operator <<(QDataStream &stream, const Schedule &schedule);
QDataStream &operator >>(QDataStream &stream, Schedule &scheule);

#endif // SCHEDULE_H
