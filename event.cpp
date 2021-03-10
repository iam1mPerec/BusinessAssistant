#include "event.h"
#include <QDataStream>
#include <QDebug>

long long Event::count = 0;

bool Event::getIsRecurring() const
{
    return isRecurring;
}

void Event::setIsRecurring(bool value)
{
    isRecurring = value;
}

Event::Event() :
    name(""),
    description(""),
    isRecurring(false),
    ID(++count)
{

}

Event::Event(long long PresetID) :
    name(""),
    description(""),
    isRecurring(false),
    ID(PresetID)
{
    if(count < ID) {
        count = ID;
    }
}

void Event::setBeginsOn(const QDate &Date)
{
    beginsOn = Date;
}

void Event::setEndsOn(const QDate &Date)
{
    endsOn = Date;
}

void Event::setName(const QString &value)
{
    name = value;
}

void Event::setDescription(const QString &value)
{
    description = value;
}

QDate Event::getBeginsOnDate() const
{
    return beginsOn;
}

QDate Event::getEndsOnDate() const
{
    return endsOn;
}

QDate Event::getNextDate() const
{
    if(!this->isRecurring) {
        return this->beginsOn;
    }
    else {
        if(QDate::currentDate().dayOfYear() <= this->beginsOn.dayOfYear()) {
            return QDate(QDate::currentDate().year(), this->beginsOn.month(), this->beginsOn.day());
        }
        else {
            return QDate(QDate::currentDate().year()+1, this->beginsOn.month(), this->beginsOn.day());
        }
    }
}

QString Event::getName() const
{
    return name;
}

QString Event::getDescription() const
{
    return description;
}

long long Event::getID() const
{
    return  ID;
}

bool Event::isRelevant(const QDate &Date) const
{
    if(!this->isRecurring) {
        return Date >= beginsOn && Date<=endsOn;
    }
    else {
        return (Date.month() >= beginsOn.month() && Date.day() >= beginsOn.day()) && (Date.month() <= endsOn.month() && Date.day() <= endsOn.day());
    }
}

QString Event::toString() const
{
    return name + " " + QString::number(beginsOn.day()) + "/" + QString::number(beginsOn.month()) + "/" + QString::number(beginsOn.year());
}


QDataStream &operator <<(QDataStream &stream, const Event &event)
{
    stream<<event.getName();
    stream<<event.getDescription();
    stream<<event.getBeginsOnDate();
    stream<<event.getEndsOnDate();
    stream<<event.getIsRecurring();

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Event &event)
{
    QString tempString;
    QDate   tempDate;

    //Getting name
    stream>>tempString;
    event.setName(tempString);

    //Getting Description
    stream>>tempString;
    event.setDescription(tempString);

    //Getting the date event begins on
    stream>>tempDate;
    event.setBeginsOn(tempDate);

    //Getting the date event ends on
    stream>>tempDate;
    event.setEndsOn(tempDate);

    //Getting is the date recurring
    bool IS_RECURRING;
    stream>>IS_RECURRING;
    event.setIsRecurring(IS_RECURRING);

    return stream;
}
