#include <QMessageBox>
#include <QDebug>
#include "NewEvent.h"
#include "ui_NewEvent.h"
#include "event.h"
#include "statics.h"

NewEvent::NewEvent(Event *Event, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEvent),
    event(Event)
{
    ui->setupUi(this);

    setDayValidator(ui->FromDay);
    setMonthValidator(ui->FromMonth);
    setYearValidator(ui->FromYear);

    setDayValidator(ui->UntilDay);
    setMonthValidator(ui->UntilMonth);
    setYearValidator(ui->UntilYear);

    if(Event->getBeginsOnDate().isValid()) {
        ui->FromDay->setText(formatDate(Event->getBeginsOnDate().day()));
        ui->FromMonth->setText(formatDate(Event->getBeginsOnDate().month()));
        ui->FromYear->setText(formatDate(Event->getBeginsOnDate().year()));

        ui->UntilDay->setText(formatDate(Event->getBeginsOnDate().day()));
        ui->UntilMonth->setText(formatDate(Event->getBeginsOnDate().month()));
        ui->UntilYear->setText(formatDate(Event->getBeginsOnDate().year()));
    }
}

NewEvent::~NewEvent()
{
    delete ui;
}

void NewEvent::on_cansel_clicked()
{
    close();
}

void NewEvent::on_save_clicked()
{
    QDate BeginsOn(ui->FromYear->text().toInt(), ui->FromMonth->text().toInt(), ui->FromDay->text().toInt());

    if(isValidText(ui->Name) && isValidDate(ui->FromYear, ui->FromMonth, ui->FromDay))
    {
        event->setName(ui->Name->text());
        event->setDescription(ui->Description->toPlainText());
        event->setBeginsOn(QDate(ui->FromYear->text().toInt(), ui->FromMonth->text().toInt(), ui->FromDay->text().toInt()));
        event->setEndsOn(QDate(ui->UntilYear->text().toInt(), ui->UntilMonth->text().toInt(), ui->UntilDay->text().toInt()));
        event->setIsRecurring(ui->isRecurring->isChecked());
        close();
    }
}
