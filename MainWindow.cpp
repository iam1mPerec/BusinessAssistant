#include <iostream>
#include "MainWindow.h"
#include "NewFacility.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addFacility_clicked()
{
    Facility facility;
    NewFacility window(facility);
    window.setModal(true);
    window.exec();
    cout<<facility.getPhone()<<endl;
    cout<<facility.getAddress()<<endl;
}
