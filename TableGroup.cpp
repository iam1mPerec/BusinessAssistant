#include "TableGroup.h"
#include "worker.h"

const QString TableGroup::yellow = "#FED23F";
const QString TableGroup::green  = "#B5D33D";
const QString TableGroup::purple = "#442288";
const QString TableGroup::red    = "#EB7D5B";
const QString TableGroup::blue   = "#6CA2EA";

const int TableGroup::numberOfColors = 5;

int TableGroup::getNumberOfColors() {
    return numberOfColors;
}

TableGroup::TableGroup(Worker *worker, QDate BeginsOn, long long NumOfDays) :
    beginsOn(BeginsOn),
    numOfDays(NumOfDays)
{
    workers.push_back(worker);
}

QDate TableGroup::getBeginsOn() const {
    return beginsOn;
}

bool TableGroup::hasColor(QDate date) const {
    if(beginsOn <= date && beginsOn.addDays(numOfDays) >= date) {
        return true;
    }
    return false;
}

bool TableGroup::hasLabel(QDate date) const {
    if(hasColor(date) && date <= beginsOn.addDays(workers.count() - 1) ) {
        return true;
    }
    return false;
}

bool TableGroup::hasWorker(long long ID) const {
    for(auto worker : workers) {
        if(worker->getID() == ID) {
            return true;
        }
    }
    return false;
}

void TableGroup::addWorker(Worker *NewWorker) {
    workers.push_back(NewWorker);
}

QString TableGroup::getWorkerName(QDate Date) const {
    return workers.at(beginsOn.daysTo(Date))->getNameAndSurname();
}
