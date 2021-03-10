#ifndef CALENDARDATEOBSERVER_H
#define CALENDARDATEOBSERVER_H

class CalendarDateObserver
{
    class Calendar* calendarSub;
public:
    CalendarDateObserver(Calendar* CalendarSub);
    void EventOnClick(class CalendarDate* date);
};

#endif // CALENDARDATEOBSERVER_H
