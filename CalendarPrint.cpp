#include "CalendarPrint.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "CalendarPrintDate.h"
#include "schedule.h"
#include "statics.h"
#include "ui_CalendarPrint.h"
#include <QDate>
#include <QDebug>

CalendarPrint::CalendarPrint(QString Name, QDate Date, QDate FiredAt, const QList<Schedule*> &Schedules, QWidget *parent) :
    QDialog(parent),
    date(Date),
    firedAt(FiredAt),
    schedules(Schedules),
    ui(new Ui::CalendarPrint)
{
    ui->setupUi(this);
    this->calendarLayout = new QGridLayout();
    this->calendarLayout->setSpacing(1);
    this->calendarLayout->setMargin(0);

    this->holidays.append(QDate(2020, 1, 1));
    this->holidays.append(QDate(2020, 1, 6));
    this->holidays.append(QDate(2020, 5, 1));
    this->holidays.append(QDate(2020, 10, 3));
    this->holidays.append(QDate(2020, 11, 1));
    this->holidays.append(QDate(2020, 12, 25));
    this->holidays.append(QDate(2020, 12, 26));

    for(int row = 0; row < 6; row++) {
        for(int column = 0; column < 7; column++) {
            CalendarPrintDate* date = new CalendarPrintDate(this);
            date->setDate(QDate::currentDate());
            this->calendarDates.append(date);
            this->calendarLayout->addWidget(date, row+2, column);
        }
    }

    ui->Worker->setText(Name);
    ui->Date->setText(Date.toString("MM/yyyy"));

    ui->CalendarWidget->setStyleSheet("QFrame{background-color: black}"
                                      "QLabel{background-color: white;}");
    ui->CalendarWidget->setLayout(this->calendarLayout);

    QDate FirstDay = Date.addDays(1 - Date.day());

    for (int day = 1; day < FirstDay.dayOfWeek(); day++) {
        this->calendarDates[FirstDay.dayOfWeek() - day -1]->setDate(FirstDay.addDays(-day));
    }

    for(int day = 0; day < FirstDay.daysInMonth(); day++) {
        calendarDates[FirstDay.dayOfWeek() + day - 1]->setDate(FirstDay.addDays(day));
    }

    for(int day = FirstDay.dayOfWeek() + FirstDay.daysInMonth() - 1, i = 0; day < calendarDates.length(); day++, i++) {
        calendarDates[day]->setDate(FirstDay.addDays(FirstDay.daysInMonth() + i));
    }

    int daysWorked = 0;

    if(!schedules.isEmpty())
    {
        for(auto calendarDate : calendarDates)
        {
            for(auto schedule : schedules)
            {
                if(calendarDate->getDate().month() == this->date.month()) {
                    if(schedule->isRelevant(calendarDate->getDate(), this->firedAt) == DateTypes::work) {
                        calendarDate->setWork();
                        daysWorked++;
                    }
                }
                else {
                    calendarDate->setBlocked();
                }
            }
            for(auto holiday : holidays) {
                if(holiday.month() == calendarDate->getDate().month() && holiday.day() == calendarDate->getDate().day()) {
                    calendarDate->setHoliday();
                }
            }
        }
    }
    ui->DaysWorked->setText("Tage gearbeitet: " + QString::number(daysWorked));
    showMaximized();
}

CalendarPrint::~CalendarPrint()
{
    delete ui;
    for(auto date : this->calendarDates) {
        delete date;
    }
    delete this->calendarLayout;
}
