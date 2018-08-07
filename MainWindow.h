#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "worker.h"
#include "facility.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addFacility_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<Worker>     workers;
    std::vector<Facility>   facilities;
};

#endif // MAINWINDOW_H
