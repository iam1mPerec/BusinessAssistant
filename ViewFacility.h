#ifndef VIEWFACILITY_H
#define VIEWFACILITY_H

#include <QDialog>

namespace Ui {
class ViewFacility;
}

class ViewFacility : public QDialog
{
    Q_OBJECT
    class Facility * facility;
    QList<class Worker *> workers;

public:
    explicit ViewFacility(Facility * Facility, const QList<class Worker *> &Workers, QWidget *parent = nullptr);
    void onDateSelected();
    void hideIrrelevant(QDate SelectedDate);
    ~ViewFacility();

private slots:
    void on_cansel_clicked();
    void on_viewDocument_clicked();
    void on_save_clicked();
    void on_print_clicked();
    void viewDocument(long long ID);

    void on_addDocument_clicked();

    void on_removeDocument_clicked();

private:
    Ui::ViewFacility *ui;
};

#endif // VIEWFACILITY_H
