#include <iostream>
#include <QFileDialog>
#include <QValidator>
#include <QDate>
#include <QDebug>
#include "ui_NewDocument.h"
#include "CustomListitem.h"
#include "NewDocument.h"
#include "document.h"
#include "statics.h"

NewDocument::NewDocument(Document *Document, QWidget *parent) :
    QDialog(parent),
    count(0),
    ui(new Ui::NewDocument),
    document(Document)
{
    ui->setupUi(this);
    setDayValidator(ui->Day);
    setMonthValidator(ui->Month);
    setYearValidator(ui->Year);
}

void NewDocument::setName(QString DocName)
{
    ui->Name->setText(DocName);
}

void NewDocument::on_cansel_clicked()
{
    this->close();
}

void NewDocument::on_document_clicked() {

    for(auto item : ui->Scans->getItems()) {
        if(item->isChecked()) {
            item->setChecked(false);
        }
    }

    CustomListitem *clickedDocument = static_cast<CustomListitem*>(sender());

    clickedDocument->setChecked(true);

    qDebug()<<clickedDocument->toolTip();

    ui->ScanImage->setPath(clickedDocument->toolTip());
}

void NewDocument::on_addScan_clicked() {

    QUrl url = QFileDialog::getOpenFileUrl();

    if(!url.isEmpty()) {
        ++count;
        CustomListitem *newDocument = new CustomListitem("Scan #"+ QString::number(count), url.toLocalFile(), this);
        newDocument->setToolTip(url.toLocalFile());
        newDocument->setCheckable(true);
        connect(newDocument, &CustomListitem::clicked, this, &NewDocument::on_document_clicked);
        ui->Scans->addItem(newDocument);
    }
}



void NewDocument::on_removeScan_clicked()
{
    for(auto item : ui->Scans->getItems()) {
        if(item->isChecked()) {
            document->removeScan(item->toolTip());
            ui->Scans->removeItem(item);
            break;
        }
    }
    ui->ScanImage->clear();
    ui->Scans->repaint();
}

void NewDocument::on_save_clicked()
{
    if(isValidText(ui->Name) && isValidDate(ui->Year, ui->Month, ui->Day))
    {
        QList<QString> scans;

        for(auto scan : ui->Scans->getItems()) {
            scans.push_back(scan->toString());
        }

        document->setDate(QDate(ui->Year->text().toInt(), ui->Month->text().toInt(), ui->Day->text().toInt()));
        document->setName(ui->Name->text());
        document->refactorScans(scans);
        close();
    }
}

NewDocument::~NewDocument()
{
    delete ui;
}
