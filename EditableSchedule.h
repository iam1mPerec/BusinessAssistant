#ifndef EDITABLESCHEDULE_H
#define EDITABLESCHEDULE_H

#include "EditableWidget.h"

class EditableSchedule : public EditableWidget
{
    int workDays, restDays;
    class widgetLineEdit * workDaysEdit;
    class widgetLineEdit * restDaysEdit;
    QWidget * ScheduleWidget;
    class QHBoxLayout * ScheduleLayout;

public:

    EditableSchedule(QWidget* parent=nullptr);

    void setSchedule(int WorkDays, int RestDays);
    void setSelected(bool);

    int getWorkDays() const;
    int getRestDays() const;

    ~EditableSchedule();

private slots:

    void onFocusLost();
};

#endif // EDITABLESCHEDULE_H
