#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include "FormContract.h"
#include "EditableWidget.h"
#include "worker.h"
#include "company.h"
#include "statics.h"
#include "Settings.h"
#include "ui_FormContract.h"

FormContract::FormContract(const Worker* Worker, QWidget *parent):
    QDialog(parent),
    worker(Worker),
    ui(new Ui::FormContract)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui->FirmPH->appendSelection("ELID");
    ui->FirmPH->appendSelection("ELID_SP");
    ui->FirmPH->select(int(worker->getFirm())-1);

    ui->ELiD->hide();
    ui->ELiD_SP->hide();

    editables.push_back(ui->FirmPH);
    editables.push_back(ui->NamePH_Boss);
    editables.push_back(ui->AddressPH_Boss);
    editables.push_back(ui->ZipTownPH_Boss);
    editables.push_back(ui->SexPH);
    editables.push_back(ui->NamePH);
    editables.push_back(ui->AddressPH);
    editables.push_back(ui->ZipTownPH);
    editables.push_back(ui->DatePH);
    editables.push_back(ui->SalaryPH);
    editables.push_back(ui->HoursPH);
    editables.push_back(ui->DatePH_2);

    settings = Settings::getInstance();

    ui->NamePH_Boss->setText(this->settings->getDirectorSurname(this->worker->getFirm()) + " " + this->settings->getDirectorName(this->worker->getFirm()));
    ui->AddressPH_Boss->setText(this->settings->getAddress(this->worker->getFirm()));
    ui->ZipTownPH_Boss->setText(this->settings->getZip(this->worker->getFirm()) + " " + this->settings->getCity(this->worker->getFirm()));
    ui->HoursPH->setText(this->settings->getHours());
    ui->SalaryPH->setText(this->settings->getRate());

    ui->SexPH->setText(worker->getTitleString());
    ui->NamePH->setText(worker->getNameAndSurname());
    ui->AddressPH->setText(worker->getAddress());
    ui->ZipTownPH->setText(worker->getZip() + " " + worker->getTown());
    ui->DatePH->setDate(QDate::currentDate());
    ui->DatePH_2->setDate(QDate::currentDate());
    for(auto editable : this->editables) {
        editable->setFontSize(24, true);
    }
}

FormContract::~FormContract()
{
    delete ui;
}

void FormContract::on_cansel_clicked()
{
    close();
}

void FormContract::on_print_clicked()
{
    Whiten(this->editables);
    switch(ui->FirmPH->getValue()) {
        case 1:
        ui->ELiD->show();
        break;
        case 2:
        ui->ELiD_SP->show();
        break;
    }
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
    deWhiten(this->editables);
}
