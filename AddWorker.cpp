#include "AddWorker.h"
#include "ui_AddWorker.h"

AddWorker::AddWorker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWorker)
{
    ui->setupUi(this);
}

AddWorker::~AddWorker()
{
    delete ui;
}
