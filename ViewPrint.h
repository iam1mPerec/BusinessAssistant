#ifndef VIEWPRINT_H
#define VIEWPRINT_H

#include <QDialog>
#include <QList>

namespace Ui {
class ViewPrint;
}

class ViewPrint : public QDialog
{
    Q_OBJECT

    static QString selectAll;
    static QString deselectAll;

    class Worker    * worker;
    class Facility  * facility;

    class QDialog * window;

public:
    explicit ViewPrint(Worker * Worker, QWidget *parent = nullptr);
    explicit ViewPrint(Facility * Facility, QWidget *parent = nullptr);

    void addDocuments(const QList<class Document*> &Documents);

    void makePDF(QString Path, QString FileName);

    ~ViewPrint();

private slots:
    void on_Print_clicked();
    void onDocumentClicked();
    void on_Cancel_clicked();

    void on_MainView_clicked();

    void on_Select_clicked();

    void on_MakePDF_clicked();

private:
    Ui::ViewPrint *ui;
};

#endif // VIEWPRINT_H
