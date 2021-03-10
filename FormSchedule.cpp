#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "FormSchedule.h"
#include "worker.h"
#include "statics.h"
#include "ui_FormSchedule.h"

FormSchedule::FormSchedule(const Worker* Worker, QStringList autoComplition, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    ui(new Ui::FormSchedule)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui->FacilityPH->setAutoComplition(autoComplition);

    ui->WorkerPH->setText(worker->getNameAndSurname());

    editables.push_back(ui->WorkerPH);
    editables.push_back(ui->FacilityPH);
    this->setFocus();
}

FormSchedule::~FormSchedule()
{
    delete ui;
}

void FormSchedule::on_cansel_clicked()
{
    close();
}

void FormSchedule::on_print_clicked()
{
    Whiten(editables);
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter;
        painter.begin(&printer);
        ui->Print->render(&painter);
        painter.end();
    }
    deWhiten(editables);
}
