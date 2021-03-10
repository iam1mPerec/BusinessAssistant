#ifndef TABLEITEMOBSERVER_H
#define TABLEITEMOBSERVER_H


class TableItemObserver
{
    class FacilityTable* facilitySubscriber;
public:
    TableItemObserver();
    TableItemObserver(FacilityTable* FacilitySubscriber);
    void subscribe(FacilityTable* subscriber);
    void notifyHoovered(const class QDate &date);
};

#endif // TABLEITEMOBSERVER_H
