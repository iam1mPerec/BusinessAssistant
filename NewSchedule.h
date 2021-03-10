#ifndef NEWSCHEDULE_H
#define NEWSCHEDULE_H

#include <QDialog>

namespace Ui {
class NewSchedule;
}

class NewSchedule : public QDialog
{
    Q_OBJECT
    class Schedule* schedule;
    QList<class Facility*> facilities;
    QList<class Schedule*> schedules;

public:
    explicit NewSchedule(class Schedule* Schedule, QList<class Schedule *> Schedules, const QList<class Facility*> &facilities, QWidget *parent = nullptr);
    ~NewSchedule();

private slots:
    void on_cansel_clicked();

    void on_save_clicked();

private:
    Ui::NewSchedule *ui;
};

#endif // NEWSCHEDULE_H
