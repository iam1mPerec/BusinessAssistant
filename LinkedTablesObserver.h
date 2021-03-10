#ifndef LINKEDTABLESOBSERVER_H
#define LINKEDTABLESOBSERVER_H

#include <QList>

class LinkedTablesObserver
{
    QList<class CustomListWidget *> subscribers;
public:
    LinkedTablesObserver();
    void notifySubscribers(CustomListWidget * sender);
    void addSubscriber(CustomListWidget* newSub);
};

#endif // LINKEDTABLESOBSERVER_H
