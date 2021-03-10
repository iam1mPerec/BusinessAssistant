#include "widgetLineEdit.h"

widgetLineEdit::widgetLineEdit(QWidget *parent) : QLineEdit (parent)
{

}

void widgetLineEdit::focusOutEvent(QFocusEvent *event)
{
    emit focusLeft();
    QLineEdit::focusOutEvent(event);
}
