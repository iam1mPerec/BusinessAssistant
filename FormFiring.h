#ifndef FORMFIRING_H
#define FORMFIRING_H

#include <QDialog>

namespace Ui {
class FormFiring;
}

class FormFiring : public QDialog
{
    Q_OBJECT
    const class Worker* worker;
    QList<class EditableWidget*> editables;
    class Settings* settings;

public:
    explicit FormFiring(const class Worker* Worker, QWidget *parent = nullptr);
    ~FormFiring();

private slots:
    void on_cansel_clicked();

    void on_print_clicked();

private:
    Ui::FormFiring *ui;
};

#endif // FORMFIRING_H
