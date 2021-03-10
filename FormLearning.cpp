#include "FormLearning.h"
#include "EditableWidget.h"
#include "ui_FormLearning.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "worker.h"
#include "Settings.h"

FormLearning::FormLearning(const Worker* Worker, QWidget *parent) :
    QDialog(parent),
    worker(Worker),
    ui(new Ui::FormLearning)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    this->settings = Settings::getInstance();

    ui->Firm->appendSelection("ELID");
    ui->Firm->appendSelection("ELID_SP");
    ui->Firm->select(int(worker->getFirm())-1);

    ui->ELiD->hide();
    ui->ELiD_SP->hide();
    ui->Date->hide();

    this->editables.append(ui->PHBegins);
    this->editables.append(ui->PHEnds_4);
    this->editables.append(ui->PHEnds_2);
    this->editables.append(ui->Firm);
    this->editables.append(ui->PHName);
    this->editables.append(ui->PHLength);
    this->editables.append(ui->PHAddress);
    this->editables.append(ui->PHTeacher);

    for(auto editable : editables) {
        editable->alignLabel(Qt::AlignCenter);
    }

    ui->PHBegins->setDate(QDate::currentDate());
    ui->PHEnds_4->setDate(QDate::currentDate());
    ui->PHEnds_2->setDate(QDate::currentDate());
    ui->PHTeacher->setText(this->settings->getSchoolTeacher(this->worker->getFirm()));
    ui->PHAddress->setText(this->settings->getSchoolAddress(this->worker->getFirm()));
    ui->PHLength->setText(this->settings->getSchoolLasts(this->worker->getFirm()));

    ui->PHName->setText(worker->getNameAndSurname());

    auto pal = ui->Print->palette();
    pal.setColor(QPalette::Window, "red");
    ui->Print->setPalette(pal);
}

void FormLearning::whiten()
{
    for(auto editable : editables) {
        editable->whiten();
    }
}

void FormLearning::deWhiten()
{
    for(auto editable : editables) {
        editable->deWhiten();
    }
}

FormLearning::~FormLearning()
{
    delete ui;
}

void FormLearning::on_cansel_clicked()
{
    close();
}



void FormLearning::on_print_clicked()
{
    QString color;
    whiten();
    ui->Date->show();
    ui->DateWidget->hide();
    ui->Date->setText(ui->PHBegins->getDate().toString("dd/MM/yyyy") + " - " + ui->PHEnds_4->getDate().toString("dd/MM/yyyy"));
    switch(ui->Firm->getValue()) {
        case 1:
        ui->ELiD->show();
        color = "blue";
        ui->PrintContent->setStyleSheet("QWidget{background-color: white; font-family: 'Times New Roman', Times, serif; font-size: 40px;} #PrintContent{border: 4px solid "+ color +";}");
        ui->Date->setStyleSheet("color: "+ color +"; font-size: 26px;");
        ui->PHName->setColor(color);
        ui->PHEnds_2->setColor(color);
        break;
        case 2:
        ui->ELiD_SP->show();
        color = "red";
        ui->PrintContent->setStyleSheet("QWidget{background-color: white; font-family: 'Times New Roman', Times, serif; font-size: 40px;} #PrintContent{border: 4px solid "+ color +";}");
        ui->Date->setStyleSheet("color: "+ color +"; font-size: 26px;");
        ui->PHName->setColor(color);
        ui->PHEnds_2->setColor(color);
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
    ui->Date->hide();
    ui->DateWidget->show();
    ui->PrintContent->setStyleSheet("QWidget{background-color: white; font-family: 'Times New Roman', Times, serif; font-size: 40px;} #PrintContent{border: none;}");
    color = "black";
    ui->PHName->setColor(color);
    ui->PHEnds_2->setColor(color);
    deWhiten();
}
