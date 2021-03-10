#ifndef WIDGETLINEEDIT_H
#define WIDGETLINEEDIT_H

#include <QLineEdit>

class widgetLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    widgetLineEdit(QWidget *parent = nullptr);
    void focusOutEvent( QFocusEvent* event);

signals:
    void focusLeft();
};

#endif // WIDGETLINEEDIT_H
