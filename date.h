#ifndef DATE_H
#define DATE_H

#include <stdio.h>

class Date {

private:
    int day;
    int month;
    int year;

    bool isLeapYear(int year) const;

public:
    Date();
    Date(int Day, int Month, int Year);

    void setDay(int Day);
    void setMonth(int Month);
    void setYear(int Year);

    int getDay()    const;
    int getMonth()  const;
    int getYear()   const;

    bool isValidDate() const;

    int getDaysToExpiration()           const;
    int getDifference(const Date &Date) const;
};


#endif // DATE_H
