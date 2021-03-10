#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>
#include "NewSchedule.h"
#include "ui_NewSchedule.h"
#include "facility.h"
#include "schedule.h"
#include "statics.h"

NewSchedule::NewSchedule(Schedule *Schedule, QList<class Schedule *> Schedules, const QList<class Facility*> &Facilities, QWidget *parent) :
    QDialog(parent),
    schedule(Schedule),
    facilities(Facilities),
    schedules(Schedules),
    ui(new Ui::NewSchedule)
{
    ui->setupUi(this);

    setDayValidator(ui->FromDay);
    setMonthValidator(ui->FromMonth);
    setYearValidator(ui->FromYear);

    setDayValidator(ui->UntilDay);
    setMonthValidator(ui->UntilMonth);
    setYearValidator(ui->UntilYear);

    setNumberValidator(ui->WorkDays);
    setNumberValidator(ui->RestDays);

    for(auto facility : facilities) {
        ui->ComboFacility->addItem(facility->getName(), facility->getID());
    }
}

void NewSchedule::on_cansel_clicked()
{
    close();
}

void NewSchedule::on_save_clicked()
{
    if(isValidDate(ui->FromYear, ui->FromMonth, ui->FromDay) && isValidDate(ui->UntilYear, ui->UntilMonth, ui->UntilDay)
            && isValidNumber(ui->WorkDays) && isValidNumber(ui->RestDays))
    {
        long long facilityID = -1;
        const QDate beginDate = QDate(ui->FromYear->text().toInt(), ui->FromMonth->text().toInt(), ui->FromDay->text().toInt());
        const QDate endDate = QDate(ui->UntilYear->text().toInt(), ui->UntilMonth->text().toInt(), ui->UntilDay->text().toInt());
        const Period period(beginDate, endDate);

        for(auto facility : facilities) {
            if(facility->getID() == ui->ComboFacility->currentData().toLongLong()) {
                facilityID = facility->getID();
                break;
            }
        }

        bool intersects = false;

        for(auto Schedule : schedules) {
            if(period.intersects(Schedule->getPeriod())) {
                intersects = true;
            }
        }

        if(facilityID == -1) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Вы не выбрали объект");
            msgBox.exec();
        }
        else if(beginDate > endDate) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("BeginDate is Lower than EndDate");
            msgBox.exec();
        }
        else if(intersects) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Работник уже занят");
            msgBox.exec();
        }
        else {
            bool hasNoScheduleConflicts = true;
            if(hasNoScheduleConflicts) {
                schedule->setBeginsOn(beginDate);
                schedule->setEndsOn(endDate);
                schedule->setFacilityID(facilityID);
                schedule->setRestDays(ui->RestDays->text().toInt());
                schedule->setWorkDays(ui->WorkDays->text().toInt());

                close();
            }
        }
    }
}

NewSchedule::~NewSchedule()
{
    delete ui;
}
