#ifndef FORMLEARNING_H
#define FORMLEARNING_H

#include <QDialog>
#include <QList>

namespace Ui {
class FormLearning;
}

class FormLearning : public QDialog
{
    Q_OBJECT

    QList<class EditableWidget*> editables;
    const class Worker* worker;
    class Settings* settings;

public:
    explicit FormLearning(const class Worker* Worker, QWidget *parent = nullptr);
    void whiten();
    void deWhiten();
    ~FormLearning();

private slots:
    void on_cansel_clicked();

    void on_print_clicked();

private:
    Ui::FormLearning *ui;
};

#endif // FORMLEARNING_H
