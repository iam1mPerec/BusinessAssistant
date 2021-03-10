#include "WorkerFormSelection.h"
#include "ui_WorkerFormSelection.h"
#include "worker.h"
#include "FormWorker.h"
#include "FormContract.h"
#include "FormSchedule.h"
#include "FormEditing.h"
#include "FormFiring.h"
#include "FormLearning.h"
#include "FormOptions.h"
#include "Settings.h"

WorkerFormSelection::WorkerFormSelection(QStringList Firms, Worker* Worker, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    firms(Firms),
    ui(new Ui::WorkerFormSelection)
{
    ui->setupUi(this);
    Settings::getInstance()->loadFromFile();
}

WorkerFormSelection::~WorkerFormSelection()
{
    delete ui;
}

void WorkerFormSelection::on_Worker_clicked()
{
    FormWorker window(worker, this);

    window.setModal(true);
    window.exec();
    this->close();
}

void WorkerFormSelection::on_Contract_clicked()
{
    FormContract window(worker, this);

    window.setModal(true);
    window.exec();
    this->close();
}

void WorkerFormSelection::on_Schedule_clicked()
{
    FormSchedule window(this->worker, this->firms, this);
    window.setModal(true);
    window.exec();
    this->close();
}

void WorkerFormSelection::on_Learning_clicked()
{
    FormLearning window(this->worker, this);

    window.setModal(true);
    window.exec();
    this->close();
}

void WorkerFormSelection::on_Firing_clicked()
{
    FormFiring window(this->worker, this);

    window.setModal(true);
    window.exec();
    this->close();
}

void WorkerFormSelection::on_Editing_clicked()
{
    FormEditing window(this->worker, this);

    window.setModal(true);
    window.exec();
    this->close();
}

void WorkerFormSelection::on_Options_clicked()
{
    FormOptions window(this);

    window.setModal(true);
    window.exec();
    window.save();
}
