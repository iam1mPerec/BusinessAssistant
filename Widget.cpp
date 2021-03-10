#include "Widget.h"

Widget::Widget(QWidget *parent) : QRadioButton(parent)
{

}

Widget::Widget(QString text, QWidget *parent) : QRadioButton(text, parent)
{

}

void Widget::focusOutEvent(QFocusEvent *event)
{
    emit focusLeft();
    QRadioButton::focusOutEvent(event);
}
