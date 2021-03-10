#include "CalendarPrintDate.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDate>
#include <QDebug>

const QString CalendarPrintDate::dayLabelDefaultStyle = "border-bottom: 1px solid black; padding: 10px 0; font-size: 20px; font-weight: bold;";

CalendarPrintDate::CalendarPrintDate(QWidget *parent) : QFrame (parent)
{
    this->layout = new QVBoxLayout;
    this->dateLabel = new QLabel;
    this->dayLabel = new QLabel;

    this->dayLabel->setAlignment(Qt::AlignCenter);
    this->dayLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    this->dayLabel->setStyleSheet(dayLabelDefaultStyle);

    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(this->dayLabel);
    layout->addWidget(this->dateLabel);
    setLayout(this->layout);
}

void CalendarPrintDate::setDate(QDate date)
{
    dayLabel->setText(QString::number(date.day()));
    this->date = date;
}

void CalendarPrintDate::setBlocked()
{
    setDateColor("lightgray");
}

void CalendarPrintDate::setWork()
{
    setDateColor("lightgreen");
}

void CalendarPrintDate::setHoliday()
{
    setDayFontColor("red");
}

void CalendarPrintDate::toDefault()
{
    this->dayLabel->setStyleSheet(dayLabelDefaultStyle);
    this->dateLabel->setStyleSheet("");
}

void CalendarPrintDate::setDayFontColor(QString color)
{
    dayLabel->setStyleSheet(dayLabel->styleSheet() + "color: " + color + ";");
}

void CalendarPrintDate::setDateColor(QString color)
{
    dateLabel->setStyleSheet("background-color: " + color + ";");
    dayLabel->setStyleSheet(dayLabelDefaultStyle + "background-color: " + color + ";");
}

QDate CalendarPrintDate::getDate() const
{
    return this->date;
}

CalendarPrintDate::~CalendarPrintDate()
{
    delete dateLabel;
    delete dayLabel;
    delete layout;
}
