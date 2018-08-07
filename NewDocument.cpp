#include <iostream>
#include <string>
#include <QFileDialog>
#include "ui_NewDocument.h"
#include "NewDocument.h"
#include "document.h"


using namespace std;

NewDocument::NewDocument(Document &Document, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDocument),
    document(Document)
{
    ui->setupUi(this);
}

NewDocument::~NewDocument()
{
    delete ui;
}

void NewDocument::on_cansel_clicked()
{
    this->close();
}

void NewDocument::on_document_clicked() {

    QPushButton *clickedDocument = static_cast<QPushButton*>(sender());

    cout<<clickedDocument->toolTip().toStdString()<<endl;

    QPixmap pixmap(clickedDocument->toolTip());

    const int w = ui->ScanImage->width();
    const int h = ui->ScanImage->height();

    ui->ScanImage->setPixmap(pixmap.scaled(w,h, Qt::KeepAspectRatio));
    bool checked = clickedDocument->isChecked();
    cout<<checked<<endl;
    clickedDocument->setChecked(checked);
}

void NewDocument::on_addScan_clicked()
{

    QUrl url = QFileDialog::getOpenFileUrl();
    if(!url.isEmpty()) {
        QPushButton *newDocument = new QPushButton("scan");
        newDocument->setToolTip(url.path());
        connect(newDocument, SIGNAL(clicked()), this, SLOT(on_document_clicked()));
        newDocument->setCheckable(true);
        ui->scrollArea->addItem(newDocument);
    }
}



void NewDocument::on_removeScan_clicked()
{

}
