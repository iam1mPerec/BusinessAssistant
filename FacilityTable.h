#ifndef FACILITYTABLE_H
#define FACILITYTABLE_H

#include <QDialog>
#include <QDate>
#include <QMap>

namespace Ui {
class FacilityTable;
}

enum Scale {
    to1,
    to2,
    to3,
    to12
};

enum SelectionState {
    firstDateSelected,
    secondDateSelected,
    noneSelected
};

enum Colors {
    yellow,
    green,
    purple,
    red,
    blue,
    extra
};

class FacilityTable : public QDialog
{
    Q_OBJECT

    static const QList<QString> colors;

    SelectionState selectionState;
    int year;
    QDate startDate;
    QDate endDate;
    Scale scale;
    QMap <QDate, class TableItem *> itemsMap;
    QList <TableItem *> itemsList;
    QList <class QWidget *> months;
    QList <class QPushButton *> buttons;
    QMap <long long, Colors> workerColors;
    int workersMarked;

    void deselectAll();
    int getBestSection(QDate Begin, QDate End) const;
    Colors getWorkersColor(long long ID);

    void extractGroups(class Schedule *schedule, class Worker *worker);
    void createGroup(class Worker *worker, QDate begins, long long numOfDays);
    void hideMonths();
    void setSchedules();
    void showMonthFromTo(const int Start, const int End);

public:
    void toggleSelectionState();
    explicit FacilityTable(class Facility *Facility, const QList<class Worker*> &Workers, int Year, QWidget *parent = nullptr);
    void mousePressEvent(class QMouseEvent *event);
    void onDateHoovered(const QDate &date);
    void hideSelectionBtns();
    void showSelectionBtns(const int lastBtn);
    void onSelectionClicked(int CurrentSelection);
    ~FacilityTable();
private slots:

    void on_btn_scale_1_clicked();
    void on_btn_scale_2_clicked();
    void on_btn_scale_3_clicked();
    void on_btn_scale_12_clicked();

    void onYearChanged();

    void on_print_clicked();

private:
    Ui::FacilityTable *ui;
    Facility *facility;
    QList<Worker*> workers;
};

#endif // FACILITYTABLE_H
