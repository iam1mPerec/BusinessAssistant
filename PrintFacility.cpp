#include "PrintFacility.h"
#include "ui_PrintFacility.h"
#include "facility.h"

PrintFacility::PrintFacility(Facility *Facility, QWidget *parent) :
    QDialog(parent),
    facility(Facility),
    ui(new Ui::PrintFacility)
{
    ui->setupUi(this);

    layout()->setAlignment(Qt::AlignTop);

    ui->Address->setText(Facility->getAddress());
    ui->Zip->setText(Facility->getZip());
    ui->Town->setText(Facility->getTown());
    ui->Owner->setText(facility->getOwner());

    setStyleSheet("background-color: white; color: black;");
}

PrintFacility::~PrintFacility()
{
    delete ui;
}
