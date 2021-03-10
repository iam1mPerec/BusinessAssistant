#include "FormFiring.h"
#include "worker.h"
#include "ui_FormFiring.h"
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include "statics.h"
#include "Settings.h"

FormFiring::FormFiring(const Worker* Worker, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    ui(new Ui::FormFiring)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    this->setFocus();
    this->settings = Settings::getInstance();

    ui->PHDate->setDate(QDate::currentDate());
    ui->PHDate_2->setDate(QDate::currentDate());

    ui->PHReasone->appendSelection("auf Ihrem Wunsch");
    ui->PHReasone->appendSelection("aus betrieblichen Gründen");
    ui->PHReasone->select(0);

    Firm firm = this->worker->getFirm();

    ui->PHFirm->appendSelection("ELID");
    ui->PHFirm->appendSelection("ELID_SP");
    ui->PHFirm->select(int(firm)-1);
    ui->PHFirm_2->appendSelection("ELID");
    ui->PHFirm_2->appendSelection("ELID_SP");
    ui->PHFirm_2->select(int(firm)-1);
    ui->PHFirm_3->appendSelection("ELID");
    ui->PHFirm_3->appendSelection("ELID_SP");
    ui->PHFirm_3->select(int(firm)-1);

    ui->PHUST->setText(this->settings->getUstNumber(firm));
    ui->PHBIC->setText(this->settings->getSwift(firm));
    ui->PHBLZ->setText(this->settings->getBlz(firm));
    ui->PHPhone->setText(this->settings->getPhone(firm));
    ui->PHMobile->setText(this->settings->getMobile(firm));
    ui->PHFax->setText(this->settings->getFax(firm));
    ui->PHKto->setText(this->settings->getKto(firm));
    ui->PHTax->setText(this->settings->getTaxNumber(firm));
    ui->PHZip->setText(this->settings->getZip(firm));
    ui->PHZip_2->setText(this->settings->getZip(firm));
    ui->PHAddress->setText(settings->getAddress(firm));
    ui->PHAddress_2->setText(settings->getAddress(firm));
    ui->PHBank->setText(this->settings->getBank(firm));
    ui->PHIBAN->setText(settings->getIban(firm));
    ui->PHCity->setText(this->settings->getCity(firm));
    ui->PHCity_2->setText(this->settings->getCity(firm));
    ui->PHNameSurname_2->setText(this->settings->getDirectorName(firm) + " " + this->settings->getDirectorSurname(firm));
    ui->PHName_boss->setText(this->settings->getDirectorName(firm) + " " + this->settings->getDirectorSurname(firm));
    ui->PHNameSurname_Boss->setText(this->settings->getDirectorName(firm)[0] + ". " + this->settings->getDirectorSurname(firm));
    ui->PHNameSurname_3->setText(this->worker->getNameAndSurname());
    ui->PHNameSurname_2->setText(this->worker->getNameAndSurname());
    ui->PHEmail->setText(settings->getEmail(firm));
    ui->PHTitle->setText(this->worker->getTitleString());
    ui->PHTown->setText(this->settings->getCity(firm));


    ui->ELiD->hide();
    ui->ELiD_SP->hide();

    editables.push_back(ui->PHUST);
    editables.push_back(ui->PHBIC);
    editables.push_back(ui->PHBLZ);
    editables.push_back(ui->PHFax);
    editables.push_back(ui->PHKto);
    editables.push_back(ui->PHTax);
    editables.push_back(ui->PHZip);
    editables.push_back(ui->PHBank);
    editables.push_back(ui->PHCity);
    editables.push_back(ui->PHDate);
    editables.push_back(ui->PHIBAN);
    editables.push_back(ui->PHEmail);
    editables.push_back(ui->PHPhone);
    editables.push_back(ui->PHZip_2);
    editables.push_back(ui->PHAddress);
    editables.push_back(ui->PHAddress_2);
    editables.push_back(ui->PHName_boss);
    editables.push_back(ui->PHCity_2);
    editables.push_back(ui->PHFirm_3);
    editables.push_back(ui->PHMobile);
    editables.push_back(ui->PHNameSurname_3);
    editables.push_back(ui->PHNameSurname_2);
    editables.push_back(ui->PHNameSurname_Boss);
    editables.push_back(ui->PHTitle);
    editables.push_back(ui->PHReasone);
    editables.push_back(ui->PHDate_2);
}

FormFiring::~FormFiring()
{
    delete ui;
}

void FormFiring::on_cansel_clicked()
{
    close();
}

void FormFiring::on_print_clicked()
{
    Whiten(editables);
    QString color;
    Firm firm = Firm::ELID;
    switch(ui->PHFirm->getValue()) {
        case 1:
        ui->ELiD->show();
        color = "blue";
        firm = Firm::ELID;
        break;
        case 2:
        ui->ELiD_SP->show();
        color = "red";
        firm = Firm::ELID_SP;
        break;
    }
    ui->PHFirm_2->select(int(firm)-1);
    ui->PHFirm_3->select(int(firm)-1);
    ui->Overline->setStyleSheet("#Overline{border-bottom: 3px solid " + color + ";}");
    ui->Underline->setStyleSheet("#Underline{border-top:  3px solid " + color + ";}");
    ui->PHFirm->hide();
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
    ui->PHFirm->show();
    ui->Overline->setStyleSheet("");
    ui->Underline->setStyleSheet("");
    deWhiten(editables);
}
