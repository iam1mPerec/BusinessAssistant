#ifndef EVENTDISPLAY_H
#define EVENTDISPLAY_H

#include <QScrollArea>

class EventDisplay : public QScrollArea
{
    Q_OBJECT

    class QWidget * contents;
    class QVBoxLayout * baseLayout;

public:
    EventDisplay(QWidget *parent = nullptr);
    void addEvent(QString Name, QString Description);
    void addEvent(class Event* event);
    void setDate(QDate NewDate);
    void onCalendarRepainted();
    void onDateSelected(const QList<class Event *> &ListOfEvents, QDate Date);
    void clear();
    ~EventDisplay();
};

#endif // EVENTDISPLAY_H
