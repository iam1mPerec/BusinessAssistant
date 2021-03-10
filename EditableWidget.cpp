#include <QDebug>
#include <QLabel>
#include <QEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QIcon>
#include "EditableWidget.h"
#include "EditableWidgetObserver.h"

EditableWidget::EditableWidget(QWidget *parent) :
QWidget(parent),
observer(nullptr),
label(nullptr),
layout(nullptr),
width(0),
height(0)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    label = new QLabel;
    layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setAlignment(this, Qt::AlignLeft);
    setFontSize(24);
    deWhiten();
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    layout->addWidget(label);
    setLayout(layout);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
    width = maximumWidth();
    height = maximumHeight();
}

bool EditableWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::FocusIn:
        setSelected(true);
        break;
    case QEvent::FocusOut:
        setSelected(false);
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

void EditableWidget::setFontSize(const int value)
{
    setFontSize(value, false);
}

void EditableWidget::setFontSize(const int value, const bool isBold)
{
    if(isBold) {
        defaultStyle = "font-size: " + QString::number(value) + "px; font-weight: bold;";
        this->label->setStyleSheet(this->label->styleSheet() + color + defaultStyle);
    }
    else {
        defaultStyle = "font-size: " + QString::number(value) + "px;";
        this->label->setStyleSheet(this->label->styleSheet() + color + defaultStyle);
    }
}

void EditableWidget::setColor(QString Color)
{
    color = "color: " + Color + ";";
    this->label->setStyleSheet(this->label->styleSheet() + color + defaultStyle);
}

void EditableWidget::alignLabel(Qt::Alignment alignment)
{
    label->setAlignment(alignment);
}

void EditableWidget::sizeLabel(const QSizePolicy::Policy horisontal, const QSizePolicy::Policy vertical)
{
    label->setSizePolicy(horisontal, vertical);
}

void EditableWidget::whiten()
{
    if(label) {
        this->label->setStyleSheet(defaultStyle + "background-color: white; padding: 0;");
    }
    setMinimumWidth(0);
    setMinimumHeight(0);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}

void EditableWidget::deWhiten()
{
    if(label) {
        this->label->setStyleSheet(defaultStyle + "background-color: lightgray; padding: 5px;");
    }
    setMinimumWidth(width);
    setMinimumHeight(height);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
}

void EditableWidget::setSelected(bool)
{
}

void EditableWidget::subscribe(EditableWidgetObserver *Observer)
{
    observer = Observer;
}

EditableWidget::~EditableWidget()
{
    delete observer;
    delete label;
    delete layout;
}
