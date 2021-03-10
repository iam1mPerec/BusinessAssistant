#ifndef RANDOMWORKERLIST_H
#define RANDOMWORKERLIST_H

#include "QList"
#include "QVector"

class RandomWorkerList
{
    QList<class Worker*> list;
    QVector<long long> candidates;
    
public:
    RandomWorkerList();
};

#endif // RANDOMWORKERLIST_H
