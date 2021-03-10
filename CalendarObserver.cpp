#include "CalendarObserver.h"
#include "EventDisplay.h"
#include "MainWindow.h"
#include "ViewFacility.h"
#include "ViewWorker.h"
#include "CustomListWidget.h"
#include "event.h"
#include "QDebug"

CalendarObserver::CalendarObserver() :
eventDisplaySub(nullptr),
mainWindow(nullptr),
viewFacility(nullptr),
viewWorker(nullptr)
{
}

void CalendarObserver::subscribe(EventDisplay *Sub)
{
    eventDisplaySub = Sub;
}

void CalendarObserver::subscribe(CustomListWidget *Sub)
{
    CustomListSubs.push_back(Sub);
}

void CalendarObserver::subscribe(MainWindow *Sub)
{
    mainWindow = Sub;
}

void CalendarObserver::subscribe(ViewFacility *Sub)
{
    viewFacility = Sub;
}

void CalendarObserver::subscribe(ViewWorker *Sub, const int workDays, const int restDays)
{
    viewWorker = Sub;
    onSubscribe(workDays, restDays);
}

void CalendarObserver::notifySubscribers(const QList<Event*> &Events, class QDate Date)
{
    if(eventDisplaySub) {
        eventDisplaySub->onDateSelected(Events, Date);
    }

    if(mainWindow) {
        mainWindow->onDateSelected();
    }

    if(viewFacility) {
        viewFacility->onDateSelected();
    }

    for(auto sub : CustomListSubs) {
        sub->onDateClicked(Date);
    }
}

void CalendarObserver::onCalendarRepaint()
{
    if(eventDisplaySub) {
        eventDisplaySub->onCalendarRepainted();
    }
}

void CalendarObserver::onWorkRestCalculation(const int WorkDays, const int RestDays)
{
    if(viewWorker) {
        viewWorker->on_work_rest_calculated(WorkDays, RestDays);
    }
}

void CalendarObserver::onSubscribe(const int WorkDays, const int RestDays)
{
    if(viewWorker) {
        viewWorker->on_work_rest_calculated(WorkDays, RestDays);
    }
}

