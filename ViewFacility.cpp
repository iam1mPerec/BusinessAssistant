#include "ViewFacility.h"
#include "ViewDocument.h"
#include "ViewPrint.h"
#include "ui_ViewFacility.h"
#include "CustomListitem.h"
#include "NewDocument.h"
#include "document.h"
#include "worker.h"
#include "facility.h"
#include <QDate>
#include <QDebug>

ViewFacility::ViewFacility(Facility * Facility, const QList<class Worker *> &Workers, QWidget *parent) :
QDialog(parent),
facility(Facility),
workers(Workers),
ui(new Ui::ViewFacility)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui->Name->setText(facility->getName());
    ui->Address->setText(facility->getAddress());
    ui->Town->setText(facility->getTown());
    ui->Zip->setText(facility->getZip());
    ui->Owner->setText(facility->getOwner());
    ui->MaxWorkers->setText(QString::number(facility->getMaxWorkers()));

    QList<QString> FIRM;
    FIRM.append("ELID");
    FIRM.append("ELID_SP");
    ui->Firm->setSelection(FIRM);
    ui->Firm->select(FIRM[int(facility->getFirm()) - 1]);

    for(auto document : facility->getDocuments()) {
        CustomListitem *newDoc = new CustomListitem(document->getName(),document->getID(),document->getExpirationDate(), this);
        connect(newDoc, SIGNAL(doubleClicked(long long)), this, SLOT(viewDocument(long long)));
        newDoc->compareWithDate(QDate::currentDate(), ui->Documents->getErgentToTop());
        ui->Documents->addItem(newDoc);
    }

    for(auto worker : workers) {
        CustomListitem *newWorkerItem = new CustomListitem(worker->getSurName() + " " + worker->getName(), worker->getID(), this);
        ui->Workers->addItem(newWorkerItem);
        newWorkerItem->hide();
    }
    ui->CalendarWidget->subscribe(this);
}

void ViewFacility::onDateSelected()
{
    hideIrrelevant(ui->CalendarWidget->getSelectedDate());
}

void ViewFacility::viewDocument(long long ID)
{
    if(ID != CustomListWidget::invalidID) {
        for(auto document : facility->getDocuments()) {
            if(document->getID() == ID) {
                ViewDocument window(document, this);
                window.setModal(true);
                window.exec();

                ui->Documents->changeItemName(ID, document->getName());
                ui->Documents->changeItemExpDate(ID, document->getExpirationDate());
            }
        }
    }
    else {
        qDebug("Something went wrong!");
    }
}

void ViewFacility::hideIrrelevant(QDate SelectedDate)
{
    for(auto worker : workers) {
        ui->Workers->getElementById(worker->getID())->setHidden(!worker->isWorking(SelectedDate, facility->getID()));
    }
}

void ViewFacility::on_viewDocument_clicked()
{
    long long id = ui->Documents->getSelectedItemID();
    viewDocument(id);
}

void ViewFacility::on_addDocument_clicked()
{
    Document* tempDocument = new Document(facility->getID(), "facilities");
    NewDocument window(tempDocument);
    window.setModal(true);
    window.exec();

    if(tempDocument->getName().isEmpty()) {
        qDebug("Document Was NOT created\n");
        delete tempDocument;
    }
    else {
        facility->addDocument(tempDocument);
        CustomListitem* Document = new CustomListitem(tempDocument->getName(), tempDocument->getID(), tempDocument->getExpirationDate(), this);
        connect(Document, SIGNAL(doubleClicked(long long)), this, SLOT(viewDocument(long long)));
        ui->Documents->addItem(Document);
        Document->compareWithDate(QDate::currentDate(), ui->Documents->getErgentToTop());
    }
}

void ViewFacility::on_save_clicked()
{
    ui->save->setFocus();
    facility->setName(ui->Name->getText());
    facility->setAddress(ui->Address->getText());
    facility->setTown(ui->Town->getText());
    facility->setZip(ui->Zip->getText());
    facility->setOwner(ui->Owner->getText());
    facility->setMaxWorkers(ui->MaxWorkers->getText().toInt());
    facility->setFirm(static_cast<Firm>(ui->Firm->getValue()));
    close();
}

void ViewFacility::on_print_clicked()
{
    ViewPrint window(facility, this);
    window.setModal(true);
    window.exec();
}

void ViewFacility::on_cansel_clicked()
{
    close();
}

ViewFacility::~ViewFacility()
{
    delete ui;
}

void ViewFacility::on_removeDocument_clicked()
{
    long long id = ui->Documents->getSelectedItemID();
    facility->removeDocument(id);
    ui->Documents->removeSelectedItem();
    ui->Documents->repaint();
}
