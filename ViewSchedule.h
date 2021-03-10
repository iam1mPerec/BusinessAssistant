#ifndef VIEWSCHEDULE_H
#define VIEWSCHEDULE_H

#include <QDialog>

namespace Ui {
class ViewSchedule;
}

class ViewSchedule : public QDialog
{
    Q_OBJECT
    class Schedule* schedule;
    QList<class Facility*> facilities;

public:
    explicit ViewSchedule(Schedule* Schedule, const QList<class Facility*> &Facilities, QWidget *parent = nullptr);
    ~ViewSchedule();

private slots:
    void on_cansel_clicked();
    void on_save_clicked();
    void on_end_clicked();

private:
    Ui::ViewSchedule *ui;
};

#endif // VIEWSCHEDULE_H
