#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QScrollArea>

class CustomListWidget : public QScrollArea
{
    Q_OBJECT
    static const int margin, spacing;
    class QWidget * contents;
    QLayout * baseLayout;
    QList<class CustomListitem*> items;
    class LinkedTablesObserver * observer;
    bool ergentToTop;

public:
    static const int invalidID;
    static const QString invalidStringID;

    static int getInvalidID();

    explicit CustomListWidget(QWidget *parent = nullptr);
    void addItem(CustomListitem *Item);
    void removeItem(CustomListitem *Item);
    void removeSelectedItem();
    void diselectItems();
    int getVisibleItemsCount();
    void addObserver(class LinkedTablesObserver * Observer);
    long long getSelectedItemID();
    CustomListitem * getElementById(long long searchID);
    CustomListitem * getElementById(QString searchID);
    void changeItemName(long long ID, QString NewName);
    void changeItemExpDate(long long ID, QDate NewDate);
    void compareWithDate(QDate selectedDate);
    void removeItemByID(long long ID);

    void sortByDate();
    void sortByName();
    void sortByExpiration();
    void sortByNameExpiration();

    void revealItems();
    bool hideUnrequestedItems(QString Key);
    bool containsID(long long ID);
    void handleClicked();

    void onDateClicked(QDate requestedDate);

    QList<class CustomListitem*> getItems() const;
    CustomListitem * extractItem(long long SearchedItemID);
    ~CustomListWidget();

    bool getErgentToTop() const;
    void setErgentToTop(bool value);

signals:

private slots:
    void onItemClicked();
};

bool dateComparator(CustomListitem* a, CustomListitem* b);
bool nameComparator(CustomListitem* a, CustomListitem* b);
bool expirationComparator(CustomListitem* a, CustomListitem* b);
bool nameExperationComparator(CustomListitem *a, CustomListitem *b);

#endif // CUSTOMLISTWIDGET_H
