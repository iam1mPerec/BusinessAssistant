#include <QVBoxLayout>
#include <QDate>
#include "EventDisplay.h"
#include "EventWidget.h"
#include "event.h"


EventDisplay::EventDisplay(QWidget *parent) :
    QScrollArea(parent)
{
    contents    = new QWidget;
    baseLayout  = new QVBoxLayout(contents);

    contents->setLayout(baseLayout);
    setWidget(contents);

    baseLayout->setAlignment(Qt::AlignTop);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

void EventDisplay::addEvent(QString Name, QString Description)
{
    EventWidget * widget = new EventWidget(Name, Description);
    baseLayout->addWidget(widget);
}

void EventDisplay::addEvent(Event *event)
{
    addEvent(event->getName(), event->getDescription());
}

void EventDisplay::setDate(QDate NewDate)
{
//    TODO Display Date!
}

void EventDisplay::onCalendarRepainted()
{
    clear();
}

void EventDisplay::onDateSelected(const QList<Event *> &ListOfEvents, QDate Date)
{
    setDate(Date);
    clear();
    for(auto event : ListOfEvents) {
        addEvent(event);
    }
}

void EventDisplay::clear()
{
    QLayoutItem *item;
    while ((item = baseLayout->takeAt(0)) != nullptr ) {
        delete item->widget();
        delete item;
    }
}

EventDisplay::~EventDisplay()
{
    clear();
    delete baseLayout;
    delete contents;
}
