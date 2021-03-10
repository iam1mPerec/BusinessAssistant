#include "FormEditing.h"
#include "worker.h"
#include "ui_FormEditing.h"
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include "statics.h"
#include "Settings.h"

FormEditing::FormEditing(const Worker* Worker, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    ui(new Ui::FormEditing)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    settings = Settings::getInstance();

    this->setFocus();

    ui->PHFirm->appendSelection("ELID");
    ui->PHFirm->appendSelection("ELID_SP");
    ui->PHFirm->select(int(worker->getFirm())-1);

    ui->ELiD->hide();
    ui->ELiD_SP->hide();
    ui->Spacer->changeSize(0,0, QSizePolicy::Maximum, QSizePolicy::Maximum);

    editables.push_back(ui->PHFirm);
    editables.push_back(ui->PHCurrentDate);
    editables.push_back(ui->PHCurrentDate_2);

    editables.push_back(ui->PHSex);
    editables.push_back(ui->PHName);
    editables.push_back(ui->PHAddress);
    editables.push_back(ui->PHZipTown);
    editables.push_back(ui->PHAddress_Boss);
    editables.push_back(ui->PHZipTown_Boss);
    editables.push_back(ui->PHName_Boss);

    ui->PHSex->setText(this->worker->getTitleString());
    ui->PHName->setText(this->worker->getNameAndSurname());
    ui->PHAddress->setText(this->worker->getAddress());
    ui->PHZipTown->setText(this->worker->getZip() + " " + this->worker->getTown());

    ui->PHName_Boss->setText(this->settings->getDirectorName(this->worker->getFirm()) + this->settings->getDirectorSurname(this->worker->getFirm()));
    ui->PHAddress_Boss->setText(this->settings->getAddress(this->worker->getFirm()));
    ui->PHZipTown_Boss->setText(this->settings->getZip(this->worker->getFirm()) + " " + this->settings->getCity(this->worker->getFirm()));

    ui->PHCurrentDate->setDate(QDate::currentDate());
    ui->PHCurrentDate_2->setDate(QDate::currentDate());
}

FormEditing::~FormEditing()
{
    delete ui;
}

void FormEditing::on_cansel_clicked()
{
    close();
}

void FormEditing::on_print_clicked()
{
    Whiten(editables);
    switch(ui->PHFirm->getValue()) {
        case 1:
        ui->ELiD->show();
        break;
        case 2:
        ui->ELiD_SP->show();
        break;
    }
    ui->Spacer->changeSize(0,0, QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter;
        painter.begin(&printer);
        ui->Print->render(&painter);
        painter.end();
    }
    ui->ELiD->hide();
    ui->ELiD_SP->hide();
    ui->Spacer->changeSize(0,0, QSizePolicy::Maximum, QSizePolicy::Maximum);
    deWhiten(editables);
}
