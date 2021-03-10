#include "HoverableLabel.h"
#include "TableItemObserver.h"
#include <QLabel>
#include <QEvent>
#include <QDebug>

QString HoverableLabel::selectedStyle = "padding: 3px; background-color: dodgerblue; color:white;";
QString HoverableLabel::layoutStyle = "padding: 1px; font-size: 9px; font-weight: bold;";

HoverableLabel::HoverableLabel(QDate Date, QWidget *parent) : QLabel(parent),
    isSelected(false),
    observer(nullptr),
    color(""),
    date(Date)
{
    toDefaultStyle();
}

void HoverableLabel::enterEvent(QEvent *event)
{
    this->QLabel::enterEvent(event);
    this->isSelected = true;
    this->toDefaultStyle();
}

void HoverableLabel::leaveEvent(QEvent *event)
{
    this->QLabel::leaveEvent(event);
    this->isSelected = false;
    this->toDefaultStyle();
}

void HoverableLabel::toDefaultStyle()
{
    if(this->isSelected) {
        setStyleSheet(selectedStyle);
    }
    else {
        if(color.isEmpty()) {
            switch(date.dayOfWeek()) {
                case 6:
                setStyleSheet("padding: 3px; background-color: lightgray;");
                break;
                case 7:
                setStyleSheet("padding: 3px; background-color: gray;");
                break;
                default:
                setStyleSheet("padding: 3px; background-color: white;");
                break;
            }
        }
        else {
            setStyleSheet("padding: 3px; background-color: " + color + ";");
        }
    }
}

void HoverableLabel::setColor(QString Color)
{
    color = Color;
    toDefaultStyle();
}

bool HoverableLabel::isFree()
{
    return color == "";
}

void HoverableLabel::subscribe(FacilityTable *subscriber)
{
    if(this->observer) {
        delete observer;
    }
    this->observer = new TableItemObserver(subscriber);
}

void HoverableLabel::setDate(QDate newDate)
{
    this->date = newDate;
    toDefaultStyle();
}

HoverableLabel::~HoverableLabel()
{
    if(this->observer) {
        delete observer;
    }
}
