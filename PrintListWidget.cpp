#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include "PrintListWidget.h"
#include "PrintListItem.h"

const int PrintListWidget::margin  = 10;
const int PrintListWidget::spacing = 18;

bool PrintListWidget::isChecked(long long ID)
{
    for(auto item : items) {
        if(item->getID() == ID) {
            return item->isChecked();
        }
    }
    return false;
}

bool PrintListWidget::hasUnchecked()
{
    for(auto item : items) {
        if(!item->isChecked()) {
            return true;
        }
    }
    return false;
}

void PrintListWidget::setAllChecked(bool state)
{
    for(auto item : items) {
        item->setChecked(state);
    }
}

PrintListWidget::PrintListWidget(QWidget *parent) :
    QScrollArea (parent)
{
    contents = new QWidget;
    layout = new QVBoxLayout(contents);
    contents->setLayout(layout);

    setWidget(contents);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(margin);
    layout->setSpacing(spacing);
}

void PrintListWidget::addItem(PrintListItem* Item)
{
    if(!items.contains(Item)) {
        items.push_back(Item);
        layout->addWidget(Item);
    }
}

