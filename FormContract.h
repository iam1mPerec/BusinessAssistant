#ifndef FORMCONTRACT_H
#define FORMCONTRACT_H

#include <QDialog>

namespace Ui {
class FormContract;
}

class FormContract : public QDialog
{
    Q_OBJECT

    QList<class EditableWidget*> editables;
    const class Worker* worker;
    class Settings* settings;

public:
    explicit FormContract(const class Worker* Worker, QWidget *parent = nullptr);
    ~FormContract();

private slots:
    void on_cansel_clicked();

    void on_print_clicked();

private:
    Ui::FormContract *ui;
};

#endif // FORMCONTRACT_H
