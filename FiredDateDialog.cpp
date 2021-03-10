#include <QString>
#include <QDate>
#include "FiredDateDialog.h"
#include "ui_FiredDateDialog.h"
#include "statics.h"

FiredDateDialog::FiredDateDialog(QDate* Date, const QDate &CurrentDate, QWidget *parent) :
    QDialog(parent),
    date(Date),
    ui(new Ui::FiredDateDialog)
{
    ui->setupUi(this);
    setDayValidator(ui->FiredAtDay);
    setMonthValidator(ui->FiredAtMonth);
    setYearValidator(ui->FiredAtYear);

    ui->FiredAtDay->setText(QString::number(CurrentDate.day()));
    ui->FiredAtMonth->setText(QString::number(CurrentDate.month()));
    ui->FiredAtYear->setText(QString::number(CurrentDate.year()));
}

void FiredDateDialog::on_save_clicked()
{
    if(isValidDate(ui->FiredAtYear, ui->FiredAtMonth, ui->FiredAtDay)) {
        date->setDate(ui->FiredAtYear->text().toInt(), ui->FiredAtMonth->text().toInt(), ui->FiredAtDay->text().toInt());
        close();
    }
}

void FiredDateDialog::on_cansel_clicked()
{
    close();
}

FiredDateDialog::~FiredDateDialog()
{
    delete ui;
}
