#ifndef CALENDARPRINT_H
#define CALENDARPRINT_H

#include <QDialog>
#include <QDate>

namespace Ui {
class CalendarPrint;
}

class   CalendarPrint : public QDialog
{
    Q_OBJECT
    class QGridLayout * calendarLayout;
    QDate date;
    QDate firedAt;
    QList<class Schedule*> schedules;
    QList<class CalendarPrintDate*> calendarDates;
    QList<QDate> holidays;
public:
    explicit CalendarPrint(QString Name, QDate Date, QDate FiredAt, const QList<class Schedule*> &Schedules, QWidget *parent = nullptr);
    ~CalendarPrint();

private:
    Ui::CalendarPrint *ui;
};

#endif // CALENDARPRINT_H
