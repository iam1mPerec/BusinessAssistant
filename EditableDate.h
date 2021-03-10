#ifndef EDITABLEDATE_H
#define EDITABLEDATE_H

#include <QDate>
#include "EditableWidget.h"

class EditableDate : public EditableWidget
{
    class QWidget * dateWidget;
    class QHBoxLayout * dateWidgetLayout;
    class widgetLineEdit * day;
    class widgetLineEdit * month;
    class widgetLineEdit * year;

    QDate date;


public:
    EditableDate(QWidget* parent=nullptr);
    void setDate(QDate date);
    void setSelected(bool);


    QDate getDate() const;

    ~EditableDate();

private slots:

    void onFocusLost();
};

#endif // EDITABLEDATE_H
