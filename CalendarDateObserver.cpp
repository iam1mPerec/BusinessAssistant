#include "CalendarDateObserver.h"
#include "NewWorker.h"
#include "Calendar.h"
#include "MainWindow.h"

CalendarDateObserver::CalendarDateObserver(Calendar *CalendarSub) :
    calendarSub(CalendarSub)
{

}

void CalendarDateObserver::EventOnClick(CalendarDate *date)
{
    if(calendarSub) {
        calendarSub->onDateClicked(date);
    }
}
