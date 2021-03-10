#ifndef FORMWORKER_H
#define FORMWORKER_H

#include <QDialog>

namespace Ui {
class FormWorker;
}

class FormWorker : public QDialog
{
    Q_OBJECT

    class Worker * worker;
    QList<class EditableWidget*> editables;

    void whiten();
    void deWhiten();

public:
    explicit FormWorker(class Worker* Worker, QWidget *parent = nullptr);
    ~FormWorker();

private slots:

    void on_cansel_clicked();

    void on_print_clicked();

private:
    Ui::FormWorker *ui;
};


#endif // FORMWORKER_H
