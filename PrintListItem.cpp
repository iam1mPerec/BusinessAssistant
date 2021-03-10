#include <QHBoxLayout>
#include <QMouseEvent>
#include <QLabel>
#include <QCheckBox>
#include "PrintListItem.h"

PrintListItem::PrintListItem(QString Name, long long ID, QWidget *parent) :
QFrame(parent),
id(ID)
{
    layout   = new QHBoxLayout();
    checkbox = new QCheckBox();
    label    = new QLabel(Name);

    setStyleSheet("border: 2px solid gray;");
    label->setStyleSheet("border: none;");
    checkbox->setStyleSheet("border: none;");

    label->setText(Name);
    layout->addWidget(checkbox);
    layout->addWidget(label);

    QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addSpacerItem(item);

    setLayout(layout);
}

long long PrintListItem::getID()
{
    return id;
}

void PrintListItem::setChecked(bool state)
{
    checkbox->setChecked(state);
}

bool PrintListItem::isChecked()
{
    return checkbox->isChecked();
}

void PrintListItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        checkbox->toggle();
        emit clicked();
    }
    else {
        event->ignore();
        return;
    }
}

PrintListItem::~PrintListItem()
{
    delete label;
    delete checkbox;
    delete layout;
}
