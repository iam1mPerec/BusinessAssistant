#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QList>
#include <QDate>

class Calendar : public QWidget
{
    Q_OBJECT

    QList<class QLabel*> DaysOfTheWeekLabels;
    QList<class CalendarDate*> calendarDates;
    QList<class Event*> events;
    QList<class Schedule*> schedules;

    QDate currentDate;
    QDate selectedDate;
    QDate functionsUntil;

    int workDays, restDays;

    class QGridLayout *CalendarLayout;
    class CalendarDateObserver * dateObserver;
    class CalendarObserver * calendarObserver;

    class QPushButton* buttonLeft;
    class QPushButton* buttonRight;
    class QPushButton* buttonToday;
    class QComboBox* comboMonth;
    class QLineEdit* lineYear;

public:
    explicit Calendar(QWidget *parent = nullptr);
    void setUpCalendar(QDate &Date);
    void setFunctionsUntil(QDate FunctionsUntil);
    void setUpCalendar();
    void setUpEvents();
    void toCurrentDate();
    void setUpSchedules();
    void notifySubscribers();
    void clearTypes();
    void setChecked(bool checked);
    void subscribe(class EventDisplay * Sub);
    void subscribe(class CustomListWidget * Sub);
    void subscribe(class MainWindow * Sub);
    void subscribe(class ViewFacility * Sub);
    void subscribe(class ViewWorker * Sub);
    void onDateClicked(CalendarDate *Day);

    QDate getSelectedDate();


    CalendarDate* getDateById(int ID);
    ~Calendar();

    void setEvents(const QList<Event*> &value);
    void addEvents(const QList<Event*> &value);
    void addEvent(Event* value);
    void removeEvent(long long ID);
    void setSchedules(const QList<Schedule *> &value);

signals:

public slots:
    void buttonLeftClicked();
    void buttonRightClicked();
    void buttonTodayClicked();
    void yearChanged();
    void monthChanged();
};

#endif // CALENDAR_H
