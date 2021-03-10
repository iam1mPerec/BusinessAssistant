#include "CustomListWidget.h"
#include "CustomListitem.h"
#include "LinkedTablesObserver.h"
#include <QDate>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

const int CustomListWidget::margin  = 10;
const int CustomListWidget::spacing = 18;
const int CustomListWidget::invalidID = 0;
const QString CustomListWidget::invalidStringID = "";

CustomListWidget::CustomListWidget(QWidget *parent) :
QScrollArea(parent),
observer(nullptr),
ergentToTop(true)
{
    contents = new QWidget;
    baseLayout = new QVBoxLayout(contents);
    contents->setLayout(baseLayout);
    setWidget(contents);
    baseLayout->setAlignment(Qt::AlignTop);
    baseLayout->setMargin(margin);
    baseLayout->setSpacing(spacing);
}

bool CustomListWidget::getErgentToTop() const
{
    return ergentToTop;
}

void CustomListWidget::setErgentToTop(bool value)
{
    ergentToTop = value;
}

int CustomListWidget::getInvalidID()
{
    return invalidID;
}

void CustomListWidget::addItem(CustomListitem * Item) {
    if(Item->getID() != this->invalidID || Item->toString() != this->invalidStringID) {
        if(!items.contains(Item)) {
            items.push_back(Item);
            baseLayout->addWidget(Item);
            Item->setHidden(false);
        }

        if(observer) {
            connect(Item, SIGNAL (clicked()), this, SLOT (onItemClicked()));
        }
    }
}

void CustomListWidget::removeItem(CustomListitem *Item)
{
    items.removeOne(Item);
    baseLayout->removeWidget(Item);
    delete Item;
}

void CustomListWidget::removeSelectedItem()
{
    for(auto item : items) {
        if(item->isChecked() && !item->isHidden()) {
            removeItem(item);
            return;
        }
    }
}

void CustomListWidget::diselectItems()
{
    for(auto item : items) {
        item->setAutoExclusive(false);

        if(item->isChecked()) {
            item->setChecked(false);
        }
    }
}

int CustomListWidget::getVisibleItemsCount()
{
    int count = 0;
    for(auto item : items) {
        if(!item->isHidden()) {
            ++count;
        }
    }
    return count;
}

void CustomListWidget::onItemClicked()
{
    for(auto item : items) {
        item->setAutoExclusive(true);
    }
    if(observer) {
        observer->notifySubscribers(this);
    }
}

void CustomListWidget::addObserver(LinkedTablesObserver *Observer)
{
    observer = Observer;
}

long long CustomListWidget::getSelectedItemID()
{
    for(auto item : items) {
        if(item->isChecked() && !item->isHidden()) {
            return item->getID();
        }
    }
    return invalidID;
}

CustomListitem *CustomListWidget::getElementById(long long searchID)
{
    if(searchID != invalidID) {
        for(auto item : items) {
            if(searchID == item->getID()) {
                return item;
            }
        }
    }
    return nullptr;
}

void CustomListWidget::removeItemByID(long long ID) {
    auto item = getElementById(ID);
    if(item) {
        removeItem(item);
    }
}

CustomListitem *CustomListWidget::getElementById(QString searchID)
{
    if(!searchID.isEmpty()) {
        for(auto item : items) {
            if(searchID == item->toString()) {
                return item;
            }
        }
    }
    return nullptr;
}

void CustomListWidget::changeItemName(long long ID, QString NewName)
{
    for(auto item : items) {
        if(item->getID() == ID) {
            item->setLabelText(NewName);
        }
    }
}

void CustomListWidget::changeItemExpDate(long long ID, QDate NewDate)
{
    for(auto item : items) {
        if(item->getID() == ID) {
            item->setExpDate(NewDate, this->ergentToTop);
            item->compareWithDate(QDate::currentDate(), this->ergentToTop);
        }
    }
}

void CustomListWidget::compareWithDate(QDate selectedDate)
{
    for(auto item : items) {
        item->compareWithDate(selectedDate, this->ergentToTop);
        item->repaint();
    }
}

void CustomListWidget::sortByDate()
{
    std::sort(items.begin(), items.end(), dateComparator);
    for(auto item : items)
    {
        baseLayout->addWidget(item);
    }
}

void CustomListWidget::sortByName()
{
    std::sort(items.begin(), items.end(), nameComparator);
    for(auto item : items)
    {
        baseLayout->addWidget(item);
    }
}

void CustomListWidget::sortByExpiration()
{
    std::sort(items.begin(), items.end(), expirationComparator);
    for(auto item : items)
    {
        baseLayout->addWidget(item);
    }
}

void CustomListWidget::sortByNameExpiration()
{
    std::sort(items.begin(), items.end(), nameExperationComparator);
    for(auto item : items)
    {
        baseLayout->addWidget(item);
    }
}

void CustomListWidget::revealItems()
{
    for(auto item : items) {
        item->setHidden(false);
    }
}

bool CustomListWidget::hideUnrequestedItems(QString Key)
{
    if(Key.isEmpty()) {
        return false;
    }

    Key = "*" + Key + "*";
    QRegExp rx(Key);
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    rx.setPatternSyntax(QRegExp::Wildcard);

    for(auto item : items) {
        if(rx.exactMatch(item->getLabelText())) {
            item->setHidden(false);
        }
        else {
            item->setHidden(true);
        }
    }
    return true;
}

bool CustomListWidget::containsID(long long ID) {
    for(auto item : items) {
        if(item->getID() == ID) {
            return true;
        }
    }
    return false;
}

void CustomListWidget::handleClicked()
{
    diselectItems();
}

void CustomListWidget::onDateClicked(QDate requestedDate)
{
    for(auto item : items) {
        item->compareWithDate(requestedDate, this->ergentToTop);
    }
}

QList<CustomListitem*> CustomListWidget::getItems() const {
    return items;
}

CustomListitem *CustomListWidget::extractItem(long long SearchedItemID)
{
    for(auto item : items) {
        if(item->getID() == SearchedItemID) {
            items.removeOne(item);
            disconnect(item, SIGNAL (clicked()), this, SLOT (onItemClicked()));
            item->setAutoExclusive(false);
            item->setChecked(false);
            return item;
        }
    }
    return nullptr;
}

CustomListWidget::~CustomListWidget()
{
    for(auto item : items) {
        delete item;
    }
    delete baseLayout;
    delete contents;
}

bool dateComparator(CustomListitem *a, CustomListitem *b)
{
    if(a->getExpDate().isValid() && b->getExpDate().isValid())
    {
        return a->getExpDate() < b->getExpDate();
    }
    else
    {
        return false;
    }
}

bool nameExperationComparator(CustomListitem *a, CustomListitem *b)
{
    return (a->getExp() < b->getExp()) || ((a->getExp() == b->getExp()) && (a->getLabelText() < b->getLabelText()));
}

bool nameComparator(CustomListitem *a, CustomListitem *b)
{
    return a->getLabelText() < b->getLabelText();
}

bool expirationComparator(CustomListitem *a, CustomListitem *b)
{
    return b->getExpDate() > a->getExpDate();
}
