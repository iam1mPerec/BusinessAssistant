#ifndef FORMSCHEDULE_H
#define FORMSCHEDULE_H

#include <QDialog>

namespace Ui {
class FormSchedule;
}

class FormSchedule : public QDialog
{
    Q_OBJECT
    QList<class EditableWidget*> editables;
    const class Worker* worker;

public:
    explicit FormSchedule(const class Worker* Worker, QStringList autoComplition, QWidget *parent = nullptr);
    ~FormSchedule();

private slots:
    void on_cansel_clicked();

    void on_print_clicked();

private:
    Ui::FormSchedule *ui;
};

#endif // FORMSCHEDULE_H
