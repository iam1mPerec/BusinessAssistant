#include <QFileDialog>
#include "ViewDocument.h"
#include "ui_ViewDocument.h"
#include "CustomListitem.h"
#include "document.h"

ViewDocument::ViewDocument(Document * Document, QWidget *parent) :
    QDialog(parent),
    document(Document),
    scansCount(0),
    ui(new Ui::ViewDocument)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui->Name->setText(document->getName());
    ui->EndsOn->setDate(document->getExpirationDate());

    scans = document->copyTemp();

    for(auto scan : scans) {
        CustomListitem *newScan = new CustomListitem("scan #" + QString::number(++scansCount), scan, this);
        newScan->setToolTip(scan);
        newScan->setCheckable(true);
        ui->Scans->addItem(newScan);
        connect(newScan, &CustomListitem::clicked, this, &ViewDocument::on_document_clicked);
    }
}

void ViewDocument::setName(QString DocName)
{
    ui->Name->setText(DocName);
}

void ViewDocument::on_document_clicked()
{
    CustomListitem *clickedDocument = static_cast<CustomListitem*>(sender());
    ui->ScanImage->setPath(clickedDocument->toolTip());
}

void ViewDocument::on_addScan_clicked()
{
    QUrl url = QFileDialog::getOpenFileUrl();

    if(!url.isEmpty()) {
        CustomListitem *newScan = new CustomListitem("Scan #"+ QString::number(++scansCount), url.toLocalFile(), this);
        newScan->setToolTip(url.toLocalFile());
        newScan->setCheckable(true);
        ui->Scans->addItem(newScan);
        scans.push_back(url.path());
        connect(newScan, &CustomListitem::clicked, this, &ViewDocument::on_document_clicked);
    }
}

void ViewDocument::on_removeScan_clicked()
{
    for(auto item : ui->Scans->getItems()) {
        if(item->isChecked()) {
            document->removeScan(item->toolTip());
            scans.removeOne(item->toolTip());
            ui->Scans->removeItem(item);
            break;
        }
    }
    ui->Scans->repaint();
}

void ViewDocument::on_save_clicked()
{
    document->setName(ui->Name->getText());
    document->setDate(ui->EndsOn->getDate());

    document->resetScansID();
    document->deleteScans();
    document->refactorScans(scans);

    close();
}

void ViewDocument::on_cansel_clicked()
{
    close();
}

ViewDocument::~ViewDocument()
{
    document->deleteTemp();
    delete ui;
}
