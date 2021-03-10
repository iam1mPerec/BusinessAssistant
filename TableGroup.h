#ifndef TABLEGROUP_H
#define TABLEGROUP_H

#include <QList>
#include <QDate>

class TableGroup
{
    QList<class Worker*> workers;
    QDate beginsOn;
    long long numOfDays;

    static const QString yellow;
    static const QString green;
    static const QString purple;
    static const QString red;
    static const QString blue;
    static const int numberOfColors;

public:
    static int getNumberOfColors();

    TableGroup(Worker *worker, QDate BeginsOn, long long numOfDays);

    void addWorker(Worker *NewWorker);
    void removeWorker(Worker *RemoveWorker);

    QDate getBeginsOn() const;

    QString getColor() const;
    QString getWorkerName(QDate date) const;

    bool hasWorker(long long ID) const;
    bool hasColor(QDate date) const;
    bool hasLabel(QDate date) const;
};

#endif // TABLEGROUP_H
