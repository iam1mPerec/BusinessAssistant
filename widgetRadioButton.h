#ifndef WIDGETRADIOBUTTON_H
#define WIDGETRADIOBUTTON_H

#include <QRadioButton>

class widgetRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit widgetRadioButton(QString Text, QWidget *parent = nullptr);
};

#endif // WIDGETRADIOBUTTON_H
