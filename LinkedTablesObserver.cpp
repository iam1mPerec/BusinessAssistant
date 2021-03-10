#include "LinkedTablesObserver.h"
#include "CustomListWidget.h"
#include <QDebug>

LinkedTablesObserver::LinkedTablesObserver()
{

}

void LinkedTablesObserver::notifySubscribers(CustomListWidget * sender)
{
    for(auto subscriber : subscribers) {
        if(subscriber != sender) {
            subscriber->handleClicked();
        }
    }
}

void LinkedTablesObserver::addSubscriber(CustomListWidget *newSub)
{
    if(!subscribers.contains(newSub)) {
        subscribers.append(newSub);
    }
}
