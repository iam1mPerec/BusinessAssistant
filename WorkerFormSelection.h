#ifndef WORKERFORMSELECTION_H
#define WORKERFORMSELECTION_H

#include <QDialog>

namespace Ui {
class WorkerFormSelection;
}

class WorkerFormSelection : public QDialog
{
    Q_OBJECT

    class Worker* worker;
    QStringList firms;

public:
    explicit WorkerFormSelection(QStringList Firms, Worker* Worker, QWidget *parent = nullptr);
    ~WorkerFormSelection();

private slots:

    void on_Worker_clicked();

    void on_Contract_clicked();

    void on_Schedule_clicked();

    void on_Learning_clicked();

    void on_Firing_clicked();

    void on_Editing_clicked();
    
    void on_Options_clicked();

private:
    Ui::WorkerFormSelection *ui;
};

#endif // WORKERFORMSELECTION_H
