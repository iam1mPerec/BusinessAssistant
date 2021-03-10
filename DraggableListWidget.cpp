#include <QVBoxLayout>
#include "DraggableListWidget.h"
#include "DraggableListItem.h"

const int DraggableListWidget::margin  = 10;
const int DraggableListWidget::spacing = 18;

DraggableListWidget::DraggableListWidget(QWidget *parent) :
QScrollArea (parent)
{
    contents = new QWidget;
    baseLayout = new QVBoxLayout(contents);
    contents->setLayout(baseLayout);
    setWidget(contents);
    baseLayout->setAlignment(Qt::AlignTop);
    baseLayout->setMargin(margin);
    baseLayout->setSpacing(spacing);
}

void DraggableListWidget::addItem(DraggableListItem* Item) {
    if(!items.contains(Item)) {
        items.push_back(Item);
        baseLayout->addWidget(Item);
    }
}
