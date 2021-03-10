#ifndef VIEWWORKER_H
#define VIEWWORKER_H

#include <QDialog>

namespace Ui {
class ViewWorker;
}

class ViewWorker : public QDialog
{
    Q_OBJECT

    class Worker * worker;
    QList<class Facility *> facilities;
    class EventWidget * eventWidget;
    class QVBoxLayout * baseEventDisplayLayout;
    class QVBoxLayout * eventDisplayLayout;
    class QVBoxLayout * spacerEventDisplayLayout;
    class QSpacerItem * eventDisplaySpacer;
    int scheduleCount;

public:
    explicit ViewWorker(Worker* Worker, const QList<class Facility*> &Facilities, QWidget *parent = nullptr);
    void on_work_rest_calculated(const int WorkDays, const int RestDays);

    void addDocument(class Document* NewDocument);
    void addEvent(class Event* newEvent);
    void addSchedule(class Schedule* NewSchedule);

    void removeDocument(const long long ID);
    void removeEvent(const long long ID);
    void removeSchedule(const long long ID);

    ~ViewWorker();

private slots:
    void on_cansel_clicked();
    void on_save_clicked();

    void on_print_clicked();

    void on_removeDocument_clicked();
    void on_removeEvent_clicked();
    void on_removeSchedule_clicked();

    void on_addSchedule_clicked();
    void on_addEvent_clicked();
    void on_addDocument_clicked();

    void on_fire_clicked();

    void on_printCalendar_clicked();

    void on_viewSchedule_clicked();
    void on_viewEvent_clicked();
    void on_viewDocument_clicked();

    void viewDocument(long long ID);
    void viewEvent(long long ID);
    void viewSchedule(long long ID);

private:
    Ui::ViewWorker *ui;
};

#endif // VIEWWORKER_H
