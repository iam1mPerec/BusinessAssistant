#ifndef NEWWORKER_H
#define NEWWORKER_H

#include <QDialog>
#include "CalendarDateObserver.h"

namespace Ui {
class NewWorker;
}

class NewWorker : public QDialog
{
    Q_OBJECT

public:

    explicit NewWorker(class Worker* Worker, const QList<class Facility*> &Facilities, QWidget *parent = nullptr);
    ~NewWorker();

private slots:

    void on_cansel_clicked();
    void on_save_clicked();

    void on_AddPassport_clicked();
    void on_AddContract_clicked();

    void on_addSchedule_clicked();
    void on_viewSchedule_clicked();
    void on_removeSchedule_clicked();

    void on_addEvent_clicked();
    void on_viewEvent_clicked();
    void on_removeEvent_clicked();

    void on_addDocument_clicked();
    void on_viewDocument_clicked();
    void on_removeDocument_clicked();

    bool openAddDocument(QString Preset);

    void on_AddA1_clicked();

    void on_AddRegestry_clicked();

    void on_addInsurance_clicked();

    void on_RBSingle_clicked();

    void on_RBMarried_clicked();

    void on_RBDivorced_clicked();

    void on_RBMale_clicked();

    void on_RBFemale_clicked();

    void on_RB_ELID_clicked();

    void on_RB_ELID_SP_clicked();

    void on_RBWidow_clicked();

private:
    Ui::NewWorker *ui;
    class Worker* worker;
    QList<class Facility*> facilities;
};

#endif // NEWWORKER_H
