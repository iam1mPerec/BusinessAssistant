#ifndef CALENDARPRINTDATE_H
#define CALENDARPRINTDATE_H

#include <QFrame>
#include <QDate>

class CalendarPrintDate : public QFrame
{
    Q_OBJECT
    class QVBoxLayout* layout;
    class QLabel* dayLabel;
    class QLabel * dateLabel;
    class QDate date;

    const static QString dayLabelDefaultStyle;

    void setDayFontColor(QString color);
    void setDateColor(QString color);
public:
    CalendarPrintDate(QWidget *parent = nullptr);
    void setDate(QDate date);
    void setBlocked();
    void setWork();
    void setHoliday();
    void toDefault();
    QDate getDate() const;

    ~CalendarPrintDate();
};

#endif // CALENDARPRINTDATE_H
