#ifndef FIREDDATEDIALOG_H
#define FIREDDATEDIALOG_H

#include <QDialog>

namespace Ui {
class FiredDateDialog;
}

class FiredDateDialog : public QDialog
{
    Q_OBJECT
    class QDate* date;

public:
    explicit FiredDateDialog(QDate* Date, const QDate &CurrentDate, QWidget *parent = nullptr);
    ~FiredDateDialog();

private slots:
    void on_save_clicked();

    void on_cansel_clicked();

private:
    Ui::FiredDateDialog *ui;
};

#endif // FIREDDATEDIALOG_H
