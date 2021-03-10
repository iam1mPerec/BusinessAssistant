#include <QGridLayout>
#include <QDate>
#include <QDebug>
#include <QMouseEvent>
#include "CalendarDate.h"
#include "CalendarDateObserver.h"

const QString DateState::baseStyle      = "font-weight:600; font-size: 20px;";
const QString DateState::CheckedStyle   = baseStyle + "background-color: orange; color: white;";
const QString DateState::UnCheckedStyle = baseStyle + "background-color: white; color: black;";
const QString DateState::DisabledStyle  = baseStyle + "background-color: white; color: '#bbbbbb';";

DateTypes DateState::getType() const
{
    return type;
}

void DateState::resetState()
{
    disabled    = false;
    checked     = false;
    event       = false;
    type        = DateTypes::none;
}

void DateState::disable()
{
    resetState();
    disabled = true;
}

void DateState::toggleChecked()
{
    checked = !checked;
}

void DateState::unCheck()
{
    checked = false;
}

void DateState::setChecked(bool Checked)
{
    checked = Checked;
}

QString DateState::getBaseStyle()
{
    if(disabled) {
        return DisabledStyle;
    }
    else {
        if(checked) {
            return CheckedStyle;
        }
        else {
            return UnCheckedStyle;
        }
    }
}

QString DateState::getPixMap()
{
    if(!disabled && !checked) {
        switch (type) {

        case DateTypes::work:
            if(event) {
                return ":/date/work_plus.png";
            }
            else {
                return ":/date/work.png";
            }
        case DateTypes::rest:
            if(event) {
                return ":/date/vacation_plus.png";
            }
            else {
                return ":/date/vacation.png";
            }
        default:
            if(event) {
                return ":/date/event.png";
            }
            else {
                return "";
            }
        }
    }
    else {
        return "";
    }
}

bool DateState::isChecked() const
{
    return checked;
}

bool DateState::isDisabled() const
{
    return disabled;
}



void DateState::setState(bool eventPresent)
{
    event = eventPresent;
}

void DateState::setState(DateTypes Type)
{
    type = Type;
}


DateState::DateState() :
type(DateTypes::none),
disabled(false),
checked(false),
event(false)
{

}

int CalendarDate::count = 0;

const int CalendarDate::ButtonSize = 70;

CalendarDate::CalendarDate(QWidget* parent):
QLabel(parent),
ID(++count),
observer(nullptr)
{
    date = new QDate();

    DateLayout = new QGridLayout;
    DateLabel  = new QLabel;

    DateLayout->addWidget(DateLabel);
    DateLayout->setAlignment(Qt::AlignCenter);
    setLayout(DateLayout);

    setStyleSheet(DateState::UnCheckedStyle);
    setScaledContents( true );
    setMinimumWidth(ButtonSize);
}

void CalendarDate::setDate(QDate Date)
{
    date->setDate(Date.year(), Date.month(), Date.day());
    DateLabel->setText(QString::number(Date.day()));
    state.resetState();
    toDefault();
}

bool CalendarDate::compareDates(const QDate &AnotherDate) const {
    return *date == AnotherDate;
}

bool CalendarDate::isDisabled() const
{
    return this->state.isDisabled();
}

int CalendarDate::getButtonSize()
{
    return ButtonSize;
}

void CalendarDate::setCount(int presetCount)
{
    count = presetCount;
}

void CalendarDate::resetCount()
{
    count = 0;
}

void CalendarDate::setState(bool eventPresent)
{
    state.setState(eventPresent);
}

void CalendarDate::setState(DateTypes Type)
{
    state.setState(Type);
}


void CalendarDate::toDefault()
{
    if( (state.getType() == DateTypes::rest || state.getType() == DateTypes::work) && !state.isDisabled()) {
        setStyleSheet(state.getBaseStyle() + " color: white");
    }
    else {
        setStyleSheet(state.getBaseStyle());
    }

    if(!state.getPixMap().isEmpty()) {
        QPixmap pixmap(state.getPixMap());
        setPixmap(pixmap.scaled(width(), height(), Qt::KeepAspectRatio));
    }
    else {
        setPixmap(QPixmap());
    }
    DateLabel->setStyleSheet("background-color: none;");
    repaint();
}

void CalendarDate::disable()
{
    state.disable();
    setPixmap(QPixmap());
    setStyleSheet(DateState::DisabledStyle);
    DateLabel->setStyleSheet(DateState::DisabledStyle);
}

void CalendarDate::diselect()
{
    state.unCheck();
}

void CalendarDate::setChecked(bool Checked)
{
    state.setChecked(Checked);
    toDefault();
}

void CalendarDate::addObserver(CalendarDateObserver *Observer)
{
    observer = Observer;
}

int CalendarDate::getID() const
{
    return ID;
}

QDate CalendarDate::getDate() const
{
    return *date;
}

CalendarDate::~CalendarDate()
{
    delete date;
}

void CalendarDate::simmulateClicked()
{
    if(!state.isDisabled()) {

        if(observer) {
            observer->EventOnClick(this);
        }
        else {
            qDebug("not subscribed\n");
        }

        state.toggleChecked();
        toDefault();
    }
}

void CalendarDate::mousePressEvent(QMouseEvent* event)
{
    if(!state.isDisabled() && event->button() == Qt::LeftButton) {

        state.toggleChecked();

        if(state.isChecked()) {
            clear();
            this->setStyleSheet(DateState::CheckedStyle);
            DateLabel->setStyleSheet("background-color: none;");
        }
        else {
            this->setStyleSheet(DateState::UnCheckedStyle);
        }

        if(observer) {
            observer->EventOnClick(this);
        }
        else {
            qDebug("not subscribed\n");
        }

        emit clicked();
    }
    else {
        event->ignore();
        return;
    }
}
