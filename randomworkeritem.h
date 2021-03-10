#ifndef RANDOMWORKERITEM_H
#define RANDOMWORKERITEM_H

#include <QDate>

enum State {
    unknown,
    assigned,
    available,
    unavailable
};

class RandomWorkerItem
{
    class Worker* worker;
    State state;
public:
    RandomWorkerItem(Worker* Worker);
    void setState(State State);
    State getState() const;
    void checkState(QDate BeginDate, QDate EndDate);
};

#endif // RANDOMWORKERITEM_H
