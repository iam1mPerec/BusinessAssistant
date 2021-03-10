#ifndef FORMEDITING_H
#define FORMEDITING_H

#include <QDialog>

namespace Ui {
class FormEditing;
}

class FormEditing : public QDialog
{
    Q_OBJECT
    const class Worker* worker;
    QList<class EditableWidget*> editables;
    class Settings* settings;

public:
    explicit FormEditing(const class Worker* Worker, QWidget *parent = nullptr);
    ~FormEditing();

private slots:
    void on_cansel_clicked();

    void on_print_clicked();

private:
    Ui::FormEditing *ui;
};

#endif // FORMEDITING_H
