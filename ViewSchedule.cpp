#include <QMessageBox>
#include <QDebug>
#include "ViewSchedule.h"
#include "schedule.h"
#include "facility.h"
#include "ui_ViewSchedule.h"

ViewSchedule::ViewSchedule(Schedule* Schedule, const QList<class Facility*> &Facilities, QWidget *parent) :
    QDialog(parent),
    schedule(Schedule),
    facilities(Facilities),
    ui(new Ui::ViewSchedule)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui->Schedule->setSchedule(schedule->getWorkDays(), schedule->getRestDays());
    ui->BeginsOn->setDate(schedule->getBeginsOnDate());
    ui->EndsOn->setDate(schedule->getEndsOnDate());

    int index = 0;
    bool found = false;

    for(auto facility : facilities) {

        ui->Facility->addItem(facility->getName(), facility->getID());

        if(facility->getID() == schedule->getFacilityID()) {
            found = true;
        }
        if(!found) {
            ++index;
        }
    }

    if(found) {
        ui->Facility->setCurrentIndex(index);
    }
}

ViewSchedule::~ViewSchedule()
{
    delete ui;
}

void ViewSchedule::on_cansel_clicked()
{
    reject();
}

void ViewSchedule::on_save_clicked()
{
    ui->save->setFocus();
    if(ui->BeginsOn->getDate() <= ui->EndsOn->getDate())
    {

        long long facilityID = -1;

        for(auto facility : facilities) {
            if(facility->getID() == ui->Facility->currentData().toLongLong()) {
                facilityID = facility->getID();
            }
        }

        if(facilities.isEmpty()) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка");
            msgBox.setModal(true);
            msgBox.setText("Вы не выбрали объект");
            msgBox.exec();
        }

        schedule->setBeginsOn(ui->BeginsOn->getDate());
        schedule->setEndsOn(ui->EndsOn->getDate());
        schedule->setFacilityID(facilityID);
        schedule->setRestDays(ui->Schedule->getRestDays());
        schedule->setWorkDays(ui->Schedule->getWorkDays());

        accept();
    }
    else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Начало события не может быть позже окончания");
        msgBox.setModal(true);
        msgBox.exec();
    }
}

void ViewSchedule::on_end_clicked()
{
    ui->EndsOn->setDate(QDate::currentDate());
}
