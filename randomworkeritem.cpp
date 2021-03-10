#include "RandomWorkerItem.h"
#include "worker.h"

RandomWorkerItem::RandomWorkerItem(Worker* Worker) :
    worker(Worker),
    state(unknown)
{

}

void RandomWorkerItem::setState(State State)
{
    state = State;
}

State RandomWorkerItem::getState() const
{
    return state;
}

void RandomWorkerItem::checkState(QDate BeginDate, QDate EndDate)
{
    if(worker->isAvailable(BeginDate, EndDate)) {
        state = available;
    }
    else {
        state = unavailable;
    }
}


