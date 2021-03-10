#include <iostream>
#include <QCommonStyle>
#include <QTextEdit>
#include <QDebug>
#include "NewFacility.h"
#include "NewDocument.h"
#include "ViewDocument.h"
#include "CustomListitem.h"
#include "facility.h"
#include "document.h"
#include "statics.h"
#include "ui_NewFacility.h"

using namespace std;

NewFacility::NewFacility(Facility* TempFacility, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFacility),
    facility(TempFacility)
{
    ui->setupUi(this);
}

void NewFacility::on_addDocument_clicked()
{
    Document* tempDocument = new Document(facility->getID(), "facilities");
    NewDocument window(tempDocument, this);
    window.setModal(true);
    window.exec();

    if(tempDocument->getName().isEmpty()) {
        delete tempDocument;
        cout<<"Document Was NOT created\n";
    }
    else {
        facility->addDocument(tempDocument);
        CustomListitem* Document = new CustomListitem(tempDocument->getName(), facility->getID() ,this);
        Document->setCheckable(true);
        ui->Documents->addItem(Document);
    }
}

void NewFacility::on_save_clicked()
{
    if(isValidText(ui->Name) && isValidText(ui->Address) && isValidText(ui->Town) && isValidText(ui->Zip) && isValidText(ui->Owner) && facility->hasFirm()) {
        facility->setName(ui->Name->text());
        facility->setAddress(ui->Address->text());
        facility->setTown(ui->Town->text());
        facility->setZip(ui->Zip->text());
        facility->setOwner(ui->Owner->text());
        facility->setMaxWorkers((ui->MaxWorkers->text().toInt()));
        accept();
    }
}

void NewFacility::on_viewDocument_clicked()
{
    long long id = ui->Documents->getSelectedItemID();
    if(id != CustomListWidget::invalidID) {
        for(auto document : facility->getDocuments()) {
            if(facility->getID() == id) {
                ViewDocument window(document, this);
                window.setModal(true);
                window.exec();
            }
        }
    }
    else {
        qDebug() << "Something went wrong!";
    }
}

void NewFacility::on_cansel_clicked()
{
    this->close();
}

NewFacility::~NewFacility()
{
    delete ui;
}

void NewFacility::on_RB_ELID_clicked()
{
    facility->setFirm(Firm::ELID);
}

void NewFacility::on_RB_ELID_SP_clicked()
{
    facility->setFirm(Firm::ELID_SP);
}
