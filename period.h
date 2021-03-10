#ifndef PERIOD_H
#define PERIOD_H

#include "QDate"

class Period
{
    QDate beginDate;
    QDate endDate;
public:
    Period(const QDate Begin, const QDate End);
    Period();

    bool intersects(const Period comparingPeriod) const;

    QDate getBeginDate() const;
    QDate getEndDate() const;

    void setBeginDate(const QDate BeginDate);
    void setEndDate(const QDate EndDate);
};

#endif // PERIOD_H
