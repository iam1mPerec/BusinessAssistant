#include <iostream>
#include <ctime>
#include "date.h"

using namespace std;

Date::Date():
day(0),
month(0),
year(0)
{
}

Date::Date(int Day, int Month, int Year):
day(Day),
month(Month),
year(Year)
{
}

void Date::setDay(int Day) {
    if (Day <= 0 || Day > 31) {
        cout<<"Wrong Day in Date entry!\n";
        cout<<"Day entry can not be " <<Day<<endl;
        cout<<"Expected number in range from 1 to 31\n";
        cout<<"**********\n";
    }
    else {
        this->day = Day;
    }
}
void Date::setMonth(int Month) {
    if (Month <= 0 || Month > 12) {
        cout<<"Wrong Month in Date entry!\n";
        cout<<"Month entry can not be " <<Month<<endl;
        cout<<"Expected number in range from 1 to 12\n";
        cout<<"**********\n";
    }
    else {
        this->month = Month;
    }
}
void Date::setYear(int Year) {
    if (Year < 0) {
        cout<<"Wrong Year in Date entry!\n";
        cout<<"Year entry can not be " <<Year<<endl;
        cout<<"Expected number is greater than 0\n";
        cout<<"**********\n";
    }
    else {
        this->year = Year;
    }
}

int Date::getDay()   const
{
    return this->day;
}
int Date::getMonth() const
{
    return this->month;
}
int Date::getYear()  const
{
    return this->year;
}

int Date::getDifference(const Date &OtherDate) const {

//    Actual Date
    struct tm actual = {0,0,0,this->day,this->month-1,this->year-1900};
    cout<<this->day<< "/" <<this->month<<"/"<<this->year<<endl;
    cout<<"**********\n";

    time_t actualDate = mktime(&actual);
    actualDate;

//    Other Date
    struct tm other = {0,0,0,OtherDate.day,OtherDate.month-1,OtherDate.year-1900};
    cout<<OtherDate.day<< "/" <<OtherDate.month<<"/"<<OtherDate.year<<endl;
    std::cout<<"**********\n";
    time_t otherDate = mktime(&other);

    if ( actualDate != (time_t)(-1) && otherDate != (time_t)(-1))
    {
        int difference = difftime(actualDate, otherDate) / (60*60*24);
        return difference;
    }

    return 0;
}

bool Date::isValidDate() const {
    bool validation = true;
        if(!(year >= 1600 && year <=2100))
            validation = false;

        if(day < 1)
            validation = false;

        switch(month)
        {
        case 2:
            if(isLeapYear(year)) {
                if(day > 29) {
                    validation = false;
                }
            }
            else {
                if(day > 28) {
                    validation = false;
                }
            }
            break;
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if(day > 31) {
                validation = false;
            }
            break;
        case 4: case 6: case 9: case 11:
            if(day > 30) {
                validation = false;
            }
            break;
        default: // the month is not between 1 and 12
            validation = false;
            break;
        }
        return validation;
}

bool Date::isLeapYear(int year) const
 {
    return(year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
 }

int Date::getDaysToExpiration() const {

//    Current Date
    time_t CurrentDate = time(nullptr);
    struct tm *currentDate = localtime(&CurrentDate);

    return getDifference(Date(currentDate->tm_mday, currentDate->tm_mon + 1, currentDate->tm_year + 1900));
}
