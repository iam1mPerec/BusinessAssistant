#ifndef WIDGET_H
#define WIDGET_H

#include <QRadioButton>

class Widget : public QRadioButton
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    explicit Widget(QString text, QWidget *parent = nullptr);
    void focusOutEvent( QFocusEvent* event);

signals:
    void focusLeft();
};

#endif // WIDGET_H
