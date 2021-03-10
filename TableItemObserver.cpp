#include "TableItemObserver.h"
#include "FacilityTable.h"
#include <QDate>

TableItemObserver::TableItemObserver() :
    facilitySubscriber(nullptr)
{
}

TableItemObserver::TableItemObserver(FacilityTable *FacilitySubscriber) :
    facilitySubscriber(FacilitySubscriber)
{
}

void TableItemObserver::subscribe(FacilityTable *subscriber)
{
    facilitySubscriber = subscriber;
}

void TableItemObserver::notifyHoovered(const QDate &date)
{
    if(facilitySubscriber) {
        facilitySubscriber->onDateHoovered(date);
    }
}
