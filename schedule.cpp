#include <QDataStream>
#include "schedule.h"
#include "CalendarDate.h"
#include "period.h"

long long Schedule::count = 0;

Schedule::Schedule() :
ID(++count),
facilityID(-1)
{

}

Schedule::Schedule(long long PresetID) :
ID(PresetID)
{
    if(count < ID) {
        count = ID;
    }
}

long long Schedule::getID() const
{
    return  ID;
}

int Schedule::getWorkDays() const
{
    return workDays;
}

int Schedule::getRestDays() const
{
    return  restDays;
}

QDate Schedule::getBeginsOnDate() const
{
    return  period.getBeginDate();
}

QDate Schedule::getEndsOnDate() const
{
    return period.getEndDate();
}

long long Schedule::getFacilityID() const
{
    return facilityID;
}

Period Schedule::getPeriod() const
{
    return this->period;
}

bool Schedule::intersects(const Period Period) const
{
    return period.intersects(Period);
}

DateTypes Schedule::isRelevant(QDate Date, QDate FiredAt) const
{
    if(!FiredAt.isNull() && Date >= FiredAt) {
        return  DateTypes::none;
    }

    if(Date >= period.getBeginDate() && Date <= period.getEndDate())
    {
        long long dayDifferance = period.getBeginDate().daysTo(Date);

        dayDifferance = dayDifferance % (workDays + restDays);

        if(dayDifferance < workDays) {
            return DateTypes::work;
        }
        else {
            return DateTypes::rest;
        }
    }
    else
    {
        return DateTypes::none;
    }
}

DateTypes Schedule::isRelevant(QDate Date) const
{
    QDate date;
    return isRelevant(Date, date);
}

void Schedule::setWorkDays(int WorkDays)
{
    workDays = WorkDays;
}

void Schedule::setRestDays(int RestDays)
{
    restDays = RestDays;
}

void Schedule::setBeginsOn(const QDate &BeginsOn)
{
    period.setBeginDate(BeginsOn);
}

void Schedule::setEndsOn(const QDate &EndsOn)
{
    period.setEndDate(EndsOn);
}

void Schedule::setFacilityID(long long NewFacilityID)
{
    facilityID = NewFacilityID;
}

QDataStream &operator <<(QDataStream &stream, const Schedule &schedule)
{
    stream << schedule.getBeginsOnDate();
    stream << schedule.getEndsOnDate();
    stream << schedule.getWorkDays();
    stream << schedule.getRestDays();
    stream << schedule.getFacilityID();
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Schedule &schedule)
{
    QDate BeginsOn;
    QDate EndsOn;
    int WorkDays;
    int RestDays;
    long long FacilityID;

    stream >> BeginsOn;
    stream >> EndsOn;
    stream >> WorkDays;
    stream >> RestDays;
    stream >> FacilityID;

    schedule.setBeginsOn(BeginsOn);
    schedule.setEndsOn(EndsOn);
    schedule.setRestDays(RestDays);
    schedule.setWorkDays(WorkDays);
    schedule.setFacilityID(FacilityID);

    return stream;
}
