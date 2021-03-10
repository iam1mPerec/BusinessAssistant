#include "widgetTextEdit.h"

widgetTextEdit::widgetTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void widgetTextEdit::focusOutEvent(QFocusEvent *event)
{
    emit focusLeft();
    QTextEdit::focusOutEvent(event);
}
