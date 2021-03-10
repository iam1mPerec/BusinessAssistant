#include <QDate>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "widgetLineEdit.h"
#include "EditableDate.h"
#include "QLineEdit"
#include "statics.h"

EditableDate::EditableDate(QWidget* parent) :
EditableWidget (parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    day   = new widgetLineEdit;
    setDayValidator(day);
    day->setFixedWidth(50);
    day->setAlignment(Qt::AlignmentFlag::AlignCenter);
    day->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    month = new widgetLineEdit;
    setMonthValidator(month);
    month->setFixedWidth(50);
    month->setAlignment(Qt::AlignmentFlag::AlignCenter);
    month->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    year  = new widgetLineEdit;
    setYearValidator(year);
    year->setFixedWidth(70);
    year->setAlignment(Qt::AlignmentFlag::AlignCenter);
    year->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);


    dateWidget = new QWidget;
    dateWidgetLayout = new QHBoxLayout;
    dateWidgetLayout->setMargin(0);
    dateWidgetLayout->setSpacing(5);
    dateWidgetLayout->setContentsMargins(0,0,10,0);
    dateWidgetLayout->setAlignment(Qt::AlignLeft);
    dateWidgetLayout->addWidget(day);
    dateWidgetLayout->addWidget(month);
    dateWidgetLayout->addWidget(year);

    dateWidget->setStyleSheet(defaultStyle);
    dateWidget->setLayout(dateWidgetLayout);
    dateWidget->hide();

    layout->addWidget(dateWidget);

    connect(day, &widgetLineEdit::focusLeft, this, &EditableDate::onFocusLost);
    connect(month, &widgetLineEdit::focusLeft, this, &EditableDate::onFocusLost);
    connect(year, &widgetLineEdit::focusLeft, this, &EditableDate::onFocusLost);
}

void EditableDate::setDate(QDate Date)
{
    if(Date.isValid()) {
        label->setText(Date.toString("dd/MM/yyyy"));
        date = Date;
    }
    else {
        qDebug("Date is not Valid @EditableDate");
    }
}
void EditableDate::setSelected(bool)
{
    if(!day->hasFocus()&&!month->hasFocus()&&!year->hasFocus()) {
        label->hide();
        dateWidget->show();
        day->setFocus();
        day->setText(formatDate(date.day()));
        month->setText(formatDate(date.month()));
        year->setText(QString::number(date.year()));
    }
}

QDate EditableDate::getDate() const
{
    return date;
}

EditableDate::~EditableDate()
{
    delete day;
    delete month;
    delete year;

    delete dateWidgetLayout;
    delete dateWidget;
}

void EditableDate::onFocusLost()
{
    if(!day->hasFocus()&&!month->hasFocus()&&!year->hasFocus()) {
        label->show();
        dateWidget->hide();
        setDate(QDate(year->text().toInt(),month->text().toInt(),day->text().toInt()));
    }
}
