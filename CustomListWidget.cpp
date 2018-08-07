#include "CustomListWidget.h"
#include <QVBoxLayout>

CustomListWidget::CustomListWidget(QWidget *parent) : QScrollArea(parent)
{
    documentsListLayout = new QVBoxLayout();
    documentsListLayout->setAlignment(Qt::AlignTop);
    documentsListLayout->setMargin(10);
    documentsListLayout->setSpacing(15);
    documentsListLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    widget = new QWidget();
}

void CustomListWidget::createItem(QWidget* item) {
    documentsListLayout->addWidget(item);
    widget->setLayout(documentsListLayout);
    setWidget(widget);
}

void CustomListWidget::addItem(QWidget * widget) {
    widget->setStyleSheet("background-color: lightgray;");
    createItem(widget);
}

void CustomListWidget::addAlertItem   (QWidget * widget) {
    widget->setStyleSheet("background-color: yellow");
    createItem(widget);
}
void CustomListWidget::addDangerItem  (QWidget * widget) {
    widget->setStyleSheet("background-color: red");
    createItem(widget);
}
void CustomListWidget::addArchivedItem(QWidget * widget) {
    widget->setStyleSheet("background-color: gray");
    createItem(widget);
}
