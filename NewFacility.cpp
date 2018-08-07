#include <iostream>
#include <string>
#include <QCommonStyle>
#include <QMessageBox>
#include "NewFacility.h"
#include "NewDocument.h"
#include "facility.h"
#include "document.h"
#include "ui_NewFacility.h"
#include <QTextEdit>

using namespace std;

NewFacility::NewFacility(Facility &TempFacility, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFacility),
    facility(TempFacility)
{
    ui->setupUi(this);
}

NewFacility::~NewFacility()
{
    delete ui;
}

void NewFacility::on_cansel_clicked()
{
    this->close();
}

void NewFacility::on_addDocument_clicked()
{
    Document tempDocument;
    NewDocument window(tempDocument);
    window.setModal(true);
    window.exec();
    if(tempDocument.getName().empty()) {
        cout<<"Document Was NOT created\n";
    }
    else {
        cout<<"Document Was created\n";
    }
}

void NewFacility::on_save_clicked()
{
    if(!ui->TextBoxPhone->text().isEmpty() && !ui->TextBoxAddress->text().isEmpty()) {
        cout<<"Saved fine \n";
    }
    else {

        if(ui->TextBoxPhone->text().isEmpty()) {
            ui->TextBoxPhone->setStyleSheet("QTextEdit{border: 2px solid red;}");
        }
        if(ui->TextBoxAddress->text().isEmpty()) {
            ui->TextBoxAddress->setStyleSheet("QTextEdit{border: 2px solid red;}");
        }
    }

//    if(!ui->TextBoxPhone->text().isEmpty() && !ui->TextBoxAddress->text().isEmpty()) {
//        string phone   = ui->TextBoxPhone->text().toStdString();
//        string address = ui->TextBoxAddress->text().toStdString();
//        facility.setPhone(ui->TextBoxPhone->text().toStdString());
//        facility.setAddress(ui->TextBoxAddress->text().toStdString());
//        cout<<"Saved fine \n";
//        this->close();
//    }
//    else {
//        QMessageBox::warning(this, "Ошибка при заполнении" ,"Нужно заполнить Адрес и Телефон");
//    }
}
