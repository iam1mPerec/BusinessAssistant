#include <QVBoxLayout>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QDebug>
#include <QFileDialog>
#include "ViewPrint.h"
#include "ui_ViewPrint.h"
#include "FormWorker.h"
#include "PrintFacility.h"
#include "PrintListWidget.h"
#include "PrintListItem.h"
#include "worker.h"
#include "facility.h"
#include "document.h"
#include "statics.h"

QString ViewPrint::selectAll    = "Выделить всё";
QString ViewPrint::deselectAll  = "Снять выделение";

ViewPrint::ViewPrint(Worker * Worker, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    facility(nullptr),
    ui(new Ui::ViewPrint)
{
    ui->setupUi(this);
    ui->Select->setText(selectAll);
    ui->Select->setAutoDefault(false);

    ui->MakePDF->setAutoDefault(false);
    ui->MainView->setAutoDefault(false);
    ui->Print->setAutoDefault(false);
    ui->Cancel->setAutoDefault(false);

    window = new FormWorker(worker);

    addDocuments(Worker->getDocuments());
}

ViewPrint::ViewPrint(Facility *Facility, QWidget *parent) :
    QDialog(parent),
    worker(nullptr),
    facility(Facility),
    ui(new Ui::ViewPrint)
{
    ui->setupUi(this);

    ui->MainView->setAutoDefault(false);
    ui->Print->setAutoDefault(false);
    ui->Cancel->setAutoDefault(false);

    window = new PrintFacility(facility);

    addDocuments(Facility->getDocuments());
}

void ViewPrint::addDocuments(const QList<Document *> &Documents)
{
    for(auto document : Documents) {
        auto item = new PrintListItem(document->getName(), document->getID(), this);
        connect(item, SIGNAL (clicked()), this, SLOT (onDocumentClicked()));
        ui->Documents->addItem(item);
    }
}

void ViewPrint::makePDF(QString Path, QString FileName)
{
    createDirectory(Path);
    QPdfWriter printer(Path + "/" + FileName);
    printer.setPageSize(QPdfWriter::A4);

    QPainter painter(&printer);

    double xscale = printer.width() / double(window->width());
    double yscale = printer.height() / double(window->height());
    double scale = qMin(xscale, yscale);
    painter.scale(scale, scale);

    bool skip = true;

    if(ui->generalInfos->isChecked()) {
        window->render(&painter);
        skip = false;
    }

    QList<Document *> docs;

    if(worker) {
        docs = worker->getDocuments();
    }
    else if(facility) {
        docs = facility->getDocuments();
    }
    else {
        qDebug("Something wierd in on_Print_clicked");
    }

    for(auto document : docs) {
        if(ui->Documents->isChecked(document->getID())) {
            for(auto scan : document->getScans()) {

                if(!skip) {
                    printer.newPage();
                }
                else {
                    skip = false;
                }

                painter.resetTransform();

                const QImage image(scan);
                const QPoint imageCoordinates(0,0);

                xscale = printer.width() / double(image.width());
                yscale = printer.height() / double(image.height());
                scale = qMin(xscale, yscale);
                painter.scale(scale, scale);

                painter.drawImage(imageCoordinates,image);
            }
        }
    }

    painter.end();
}

void ViewPrint::onDocumentClicked()
{
    if(ui->Documents->hasUnchecked()) {
        ui->Select->setText(selectAll);
    }
    else {
        ui->Select->setText(deselectAll);
    }
}

void ViewPrint::on_Print_clicked()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter;
        painter.begin(&printer);

        bool skip = true;

        if(ui->generalInfos->isChecked()) {
            window->render(&painter);
            skip = false;
        }

        QList<Document *> docs;

        if(worker) {
            docs = worker->getDocuments();
        }
        else if(facility) {
            docs = facility->getDocuments();
        }
        else {
            qDebug("Something wierd in on_Print_clicked");
        }

        for(auto document : docs) {
            if(ui->Documents->isChecked(document->getID())) {
                for(auto scan : document->getScans()) {

                    if(!skip) {
                        printer.newPage();
                    }
                    else {
                        skip = false;
                    }

                    painter.resetTransform();

                    const QImage image(scan);

                    double xscale = printer.width() / double(image.width());
                    double yscale = printer.height() / double(image.height());
                    double scale = qMin(xscale, yscale);
                    painter.scale(scale, scale);

                    painter.drawImage(QPoint(0,0), image);
                }
            }
        }
        painter.end();
    }
}

void ViewPrint::on_MakePDF_clicked()
{
    QString Path = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), QDir::currentPath());
    if (!Path.isEmpty()) {
        qDebug() << Path;
    }
    QString name;
    if(worker) {
        name = worker->getName() + "_" + worker->getSurName() + "_" + QString::number(worker->getID()) + ".pdf";
    }
    else if(facility) {
        name = facility->getName() + "_" + QString::number(facility->getID()) + ".pdf";
    }

    makePDF(Path, name);
}

void ViewPrint::on_Cancel_clicked()
{
   close();
}

void ViewPrint::on_MainView_clicked()
{
    window->setModal(true);
    window->exec();
}

void ViewPrint::on_Select_clicked()
{
    if(ui->Documents->hasUnchecked()) {
        ui->Documents->setAllChecked(true);
        ui->Select->setText(deselectAll);
    }
    else {
        ui->Documents->setAllChecked(false);
        ui->Select->setText(selectAll);
    }
}

ViewPrint::~ViewPrint()
{
    delete window;
    delete ui;
}
