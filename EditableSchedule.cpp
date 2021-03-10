#include <QLineEdit>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "EditableSchedule.h"
#include "widgetLineEdit.h"
#include "statics.h"

EditableSchedule::EditableSchedule(QWidget *parent) :
EditableWidget (parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    setFixedHeight(40);

    ScheduleWidget = new QWidget;
    ScheduleWidget->setMaximumWidth(160);

    ScheduleLayout = new QHBoxLayout;
    ScheduleLayout->setMargin(0);
    ScheduleLayout->setSpacing(0);

    workDaysEdit = new widgetLineEdit;
    setNumberValidator(workDaysEdit);
    workDaysEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);

    restDaysEdit = new widgetLineEdit;
    setNumberValidator(restDaysEdit);
    restDaysEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);

    ScheduleLayout->addWidget(workDaysEdit);
    ScheduleLayout->addWidget(restDaysEdit);

    ScheduleWidget->setStyleSheet(defaultStyle);
    ScheduleWidget->setLayout(ScheduleLayout);
    ScheduleWidget->hide();

    layout->addWidget(ScheduleWidget);

    restDaysEdit->setStyleSheet("color: black;");
    workDaysEdit->setStyleSheet("color: black;");

    connect(workDaysEdit, &widgetLineEdit::focusLeft, this, &EditableSchedule::onFocusLost);
    connect(restDaysEdit, &widgetLineEdit::focusLeft, this, &EditableSchedule::onFocusLost);
}

void EditableSchedule::setSchedule(int WorkDays, int RestDays)
{
    workDays = WorkDays;
    restDays = RestDays;
    label->setText(QString::number(WorkDays) + "   через   " + QString::number(RestDays));
}

void EditableSchedule::setSelected(bool)
{
    if(!workDaysEdit->hasFocus()&&!restDaysEdit->hasFocus()) {
        label->hide();
        ScheduleWidget->show();
        workDaysEdit->setFocus();

        workDaysEdit->setText(QString::number(workDays));
        restDaysEdit->setText(QString::number(restDays));
    }
}

int EditableSchedule::getWorkDays() const
{
    return workDays;
}

int EditableSchedule::getRestDays() const
{
    return  restDays;
}

EditableSchedule::~EditableSchedule()
{
    delete workDaysEdit;
    delete restDaysEdit;
    delete ScheduleLayout;
    delete ScheduleWidget;
}

void EditableSchedule::onFocusLost()
{
    if(!workDaysEdit->hasFocus()&&!restDaysEdit->hasFocus()) {
        label->show();
        ScheduleWidget->hide();

        setSchedule(workDaysEdit->text().toInt(), restDaysEdit->text().toInt());
    }
}
