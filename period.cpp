#include "period.h"
#include "QDebug"

Period::Period(const QDate Begin, const QDate End) :
    beginDate(Begin),
    endDate(End)
{

}

Period::Period()
{

}

bool Period::intersects(const Period comparingPeriod) const
{
    return !(comparingPeriod.getEndDate() < this->beginDate || this->endDate < comparingPeriod.beginDate);
}
QDate Period::getBeginDate() const
{
    return this->beginDate;
}

QDate Period::getEndDate() const
{
    return this->endDate;
}

void Period::setBeginDate(const QDate BeginDate)
{
    this->beginDate = BeginDate;
}

void Period::setEndDate(const QDate EndDate)
{
    this->endDate = EndDate;
}


