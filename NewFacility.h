#ifndef NEWFACILITY_H
#define NEWFACILITY_H

#include <QDialog>

namespace Ui {
class NewFacility;
}

class NewFacility : public QDialog
{
    Q_OBJECT

public:
    explicit NewFacility(class Facility* Facility, QWidget *parent = nullptr);
    ~NewFacility();

private slots:

    void on_cansel_clicked();
    void on_addDocument_clicked();
    void on_save_clicked();
    void on_viewDocument_clicked();

    void on_RB_ELID_clicked();

    void on_RB_ELID_SP_clicked();

private:
    Ui::NewFacility *ui;
    class Facility* facility;
};

#endif // NEWFACILITY_H
