#include "FormOptions.h"
#include "Settings.h"
#include "ui_FormOptions.h"
#include <QDebug>

FormOptions::FormOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormOptions)
{
    ui->setupUi(this);

    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    this->setFocus();

    this->settings = Settings::getInstance();
    load();
}

void FormOptions::load()
{
    ui->hours->setText(settings->getHours());
    ui->rate->setText(settings->getRate());

    ui->ELID_directorName->setText(settings->getDirectorName(Firm::ELID));
    ui->ELID_directorSurname->setText(settings->getDirectorSurname(Firm::ELID));
    ui->ELID_address->setText(settings->getAddress(Firm::ELID));
    ui->ELID_zip->setText(settings->getZip(Firm::ELID));
    ui->ELID_city->setText(settings->getCity(Firm::ELID));
    ui->ELID_email->setText(settings->getEmail(Firm::ELID));
    ui->ELID_phone->setText(settings->getPhone(Firm::ELID));
    ui->ELID_fax->setText(settings->getFax(Firm::ELID));
    ui->ELID_mobile->setText(settings->getMobile(Firm::ELID));
    ui->ELID_tax->setText(settings->getTaxNumber(Firm::ELID));
    ui->ELID_ust->setText(settings->getUstNumber(Firm::ELID));
    ui->ELID_bank->setText(settings->getBank(Firm::ELID));
    ui->ELID_blz->setText(settings->getBlz(Firm::ELID));
    ui->ELID_kto->setText(settings->getKto(Firm::ELID));
    ui->ELID_iban->setText(settings->getIban(Firm::ELID));
    ui->ELID_swift->setText(settings->getSwift(Firm::ELID));
    ui->ELID_schoolAddress->setText(settings->getSchoolAddress(Firm::ELID));
    ui->ELID_schoolTeacher->setText(settings->getSchoolTeacher(Firm::ELID));
    ui->ELID_schoolLasts->setText(settings->getSchoolLasts(Firm::ELID));


    ui->ELID_SP_directorName->setText(settings->getDirectorName(Firm::ELID_SP));
    ui->ELID_SP_directorSurname->setText(settings->getDirectorSurname(Firm::ELID_SP));
    ui->ELID_SP_address->setText(settings->getAddress(Firm::ELID_SP));
    ui->ELID_SP_zip->setText(settings->getZip(Firm::ELID_SP));
    ui->ELID_SP_city->setText(settings->getCity(Firm::ELID_SP));
    ui->ELID_SP_email->setText(settings->getEmail(Firm::ELID_SP));
    ui->ELID_SP_phone->setText(settings->getPhone(Firm::ELID_SP));
    ui->ELID_SP_fax->setText(settings->getFax(Firm::ELID_SP));
    ui->ELID_SP_mobile->setText(settings->getMobile(Firm::ELID_SP));
    ui->ELID_SP_tax->setText(settings->getTaxNumber(Firm::ELID_SP));
    ui->ELID_SP_ust->setText(settings->getUstNumber(Firm::ELID_SP));
    ui->ELID_SP_bank->setText(settings->getBank(Firm::ELID_SP));
    ui->ELID_SP_blz->setText(settings->getBlz(Firm::ELID_SP));
    ui->ELID_SP_kto->setText(settings->getKto(Firm::ELID_SP));
    ui->ELID_SP_iban->setText(settings->getIban(Firm::ELID_SP));
    ui->ELID_SP_swift->setText(settings->getSwift(Firm::ELID_SP));
    ui->ELID_SP_schoolAddress->setText(settings->getSchoolAddress(Firm::ELID_SP));
    ui->ELID_SP_schoolTeacher->setText(settings->getSchoolTeacher(Firm::ELID_SP));
    ui->ELID_SP_schoolLasts->setText(settings->getSchoolLasts(Firm::ELID_SP));
}

void FormOptions::save()
{
    settings->setHours(ui->hours->getText());
    settings->setRate(ui->rate->getText());

    settings->setDirectorName(Firm::ELID, ui->ELID_directorName->getText());
    settings->setDirectorSurname(Firm::ELID, ui->ELID_directorSurname->getText());
    settings->setAddress(Firm::ELID, ui->ELID_address->getText());
    settings->setZip(Firm::ELID, ui->ELID_zip->getText());
    settings->setCity(Firm::ELID, ui->ELID_city->getText());
    settings->setEmail(Firm::ELID, ui->ELID_email->getText());
    settings->setPhone(Firm::ELID, ui->ELID_phone->getText());
    settings->setFax(Firm::ELID, ui->ELID_fax->getText());
    settings->setMobile(Firm::ELID, ui->ELID_mobile->getText());

    settings->setTaxNumber(Firm::ELID, ui->ELID_tax->getText());
    settings->setUstNumber(Firm::ELID, ui->ELID_ust->getText());

    settings->setBank(Firm::ELID, ui->ELID_bank->getText());
    settings->setBlz(Firm::ELID, ui->ELID_blz->getText());
    settings->setKto(Firm::ELID, ui->ELID_kto->getText());
    settings->setIban(Firm::ELID, ui->ELID_iban->getText());
    settings->setSwift(Firm::ELID, ui->ELID_swift->getText());

    settings->setSchoolAddress(Firm::ELID, ui->ELID_schoolAddress->getText());
    settings->setSchoolTeacher(Firm::ELID, ui->ELID_schoolTeacher->getText());
    settings->setSchoolLasts(Firm::ELID, ui->ELID_schoolLasts->getText());


    settings->setDirectorName(Firm::ELID_SP, ui->ELID_SP_directorName->getText());
    settings->setDirectorSurname(Firm::ELID_SP, ui->ELID_SP_directorSurname->getText());
    settings->setAddress(Firm::ELID_SP, ui->ELID_SP_address->getText());
    settings->setZip(Firm::ELID_SP, ui->ELID_SP_zip->getText());
    settings->setCity(Firm::ELID_SP, ui->ELID_SP_city->getText());
    settings->setEmail(Firm::ELID_SP, ui->ELID_SP_email->getText());
    settings->setPhone(Firm::ELID_SP, ui->ELID_SP_phone->getText());
    settings->setFax(Firm::ELID_SP, ui->ELID_SP_fax->getText());
    settings->setMobile(Firm::ELID_SP, ui->ELID_SP_mobile->getText());

    settings->setTaxNumber(Firm::ELID_SP, ui->ELID_SP_tax->getText());
    settings->setUstNumber(Firm::ELID_SP, ui->ELID_SP_ust->getText());

    settings->setBank(Firm::ELID_SP, ui->ELID_SP_bank->getText());
    settings->setBlz(Firm::ELID_SP, ui->ELID_SP_blz->getText());
    settings->setKto(Firm::ELID_SP, ui->ELID_SP_kto->getText());
    settings->setIban(Firm::ELID_SP, ui->ELID_SP_iban->getText());
    settings->setSwift(Firm::ELID_SP, ui->ELID_SP_swift->getText());

    settings->setSchoolAddress(Firm::ELID_SP, ui->ELID_SP_schoolAddress->getText());
    settings->setSchoolTeacher(Firm::ELID_SP, ui->ELID_SP_schoolTeacher->getText());
    settings->setSchoolLasts(Firm::ELID_SP, ui->ELID_SP_schoolLasts->getText());

    settings->saveToFile();
}

FormOptions::~FormOptions()
{
    delete ui;
}
