#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "EnumFirm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void saveFacilities();
    void saveWorkers();
    void saveEvents();

    void addFacility(class Facility *NewFacility);
    void addWorker(class Worker *NewWorker);
    void addPublicEvent(class Event *NewEvent);

    void viewWorker(long long ID);
    void viewFacility(long long ID);
    void viewEvent(long long ID);

    void sortSchedules();

    void checkWorkersOnFirm();
    void checkFacilitiesOnFirm();
    void hideWorkers(Firm firm);
    void searchWorkersByFirm(Firm firm);
    void hideFacilities(Firm firm);
    void searchFacilitiesByFirm(Firm firm);

    void sortFacilities();

    void onDateSelected();

    ~MainWindow();

private:
    static const QString savePath;
    Ui::MainWindow *ui;
    QList<class Worker*>   workers;
    QList<class Facility*> facilities;
    QList<class Event*>    publicEvents;
    QList<class Event*>    privateEvents;
    bool m_safeToClose;
    bool m_events_backed;
    bool m_facilities_backed;
    bool m_workers_backed;
    class LinkedTablesObserver * linkedTablesObserver;

    QString choosePath(const QString Path, bool &backed) const;
    QDate getTimestamp(const QString Path)const;
    void addPrivateEvents(Worker * Worker);
    void removePrivateEvents(Worker * Worker);
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_addFacility_clicked();
    void on_addWorker_clicked();
    void on_addEvent_clicked();

    void on_removeFacility_clicked();
    void on_removeWorker_clicked();
    void on_removeEvent_clicked();

    void on_viewFacility_clicked();
    void on_viewWorker_clicked();
    void on_viewEvent_clicked();

    void on_searchFacilities_clicked();
    void on_searchWorkers_clicked();
    void on_searchEvents_clicked();

    void on_canselFacilitiesSearch_clicked();
    void on_canselWorkersSearch_clicked();
    void on_canselEventsSearch_clicked();

    void on_ShowFiredCheckBox_stateChanged(int state);
    void onWorkerClicked(long long ID);
    void onFacilityClicked(long long ID);
    void onEventClicked(long long ID);
    void on_viewWorkerForms_clicked();
    void on_tableFacility_clicked();

    void on_sortWorkersELID_SP_clicked();
    void on_sortWorkersELID_clicked();
    void on_sortFacilitiesELID_clicked();
    void on_sortFacilitiesELID_SP_clicked();
};

#endif // MAINWINDOW_H
