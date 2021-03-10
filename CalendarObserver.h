#ifndef CALENDAROBSERVER_H
#define CALENDAROBSERVER_H

#include <QList>

class CalendarObserver
{
    class EventDisplay * eventDisplaySub;
    class MainWindow * mainWindow;
    class ViewFacility * viewFacility;
    class ViewWorker * viewWorker;
    QList <class CustomListWidget *> CustomListSubs;
public:
    CalendarObserver();

    void subscribe(EventDisplay * Sub);
    void subscribe(CustomListWidget * Sub);
    void subscribe(MainWindow * Sub);
    void subscribe(ViewFacility * Sub);
    void subscribe(ViewWorker * Sub, const int workDays, const int restDays);

    void notifySubscribers(const QList<class Event*> &Events, class QDate Date);
    void onCalendarRepaint();
    void onWorkRestCalculation(const int WorkDays, const int RestDays);
    void onSubscribe(const int WorkDays, const int RestDays);
};

#endif // CALENDAROBSERVER_H
