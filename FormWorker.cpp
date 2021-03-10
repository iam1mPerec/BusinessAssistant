#include "FormWorker.h"
#include "ui_FormWorker.h"
#include "worker.h"
#include "QPrinter"
#include "QPainter"
#include "QPrintDialog"
#include "EditableWidget.h"

FormWorker::FormWorker(Worker* Worker, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    ui(new Ui::FormWorker)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    this->setFocus();

    ui->Firm->appendSelection("ELID");
    ui->Firm->appendSelection("ELID_SP");
    ui->Firm->select(int(worker->getFirm())-1);

    ui->ELiD->hide();
    ui->ELiD_SP->hide();

    ui->Name->setText(Worker->getName());
    ui->Surname->setText(Worker->getSurName());
    ui->Birthname->setText(Worker->getBirthName());
    ui->BirthDate->setText(Worker->getBirthDate().toString("dd/MM/yyyy"));
    ui->PlaceOfBirth->setText(Worker->getPlaceOfBirth());
    ui->Citizenship->setText(Worker->getCitizenship());
    ui->Address->setText(Worker->getAddress());
    ui->TownZip->setText(Worker->getTown() + " " + Worker->getZip());
    ui->MaritialStatus->setText(worker->getStatusString());
    ui->Phone->setText(Worker->getPhone());
    ui->EMail->setText(Worker->getEmail());

    editables.push_back(ui->Firm);
    editables.push_back(ui->Name);
    editables.push_back(ui->Surname);
    editables.push_back(ui->Birthname);
    editables.push_back(ui->BirthDate);
    editables.push_back(ui->PlaceOfBirth);
    editables.push_back(ui->Citizenship);
    editables.push_back(ui->Address);
    editables.push_back(ui->TownZip);
    editables.push_back(ui->MaritialStatus);
    editables.push_back(ui->Phone);
    editables.push_back(ui->EMail);
}

void FormWorker::whiten()
{
    for(auto editable : editables) {
        editable->whiten();
    }
}

void FormWorker::deWhiten()
{
    for(auto editable : editables) {
        editable->deWhiten();
    }
}

FormWorker::~FormWorker()
{
    delete ui;
}

void FormWorker::on_print_clicked()
{
    whiten();
    ui->Firm->hide();
    switch(ui->Firm->getValue()) {
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
    ui->Firm->show();
    deWhiten();
}

void FormWorker::on_cansel_clicked()
{
    close();
}
