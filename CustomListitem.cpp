#include "CustomListitem.h"
#include "EnumStates.h"
#include <QDate>
#include <QLabel>
#include <QHBoxLayout>

const QString CustomListitem::NormalStyle  = "&:hover { background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(60, 186, 162, 255), stop:1 rgba(98, 211, 162, 255))} { background-color: #3cbaa2; border: 1px solid black; border-radius: 5px; } &:disabled { background-color: rgb(170, 170, 127)}";
const QString CustomListitem::AlertStyle   = "color: green";
const QString CustomListitem::WarningStyle = "color: darkred";
const QString CustomListitem::HighlightedStyle = "color: goldenrod";
const int CustomListitem::fontSize = 12;
const int CustomListitem::itemHeight = 50;


CustomListitem::CustomListitem(const QString &Text, const long long Identifier, QWidget *parent) :
    QPushButton(parent),
    ID(Identifier),
    string(""),
    exp(expiration::normal)
{
    label = new QLabel(Text);
    QFont Font = font();
    Font.setPointSize(fontSize);
    label->setFont(Font);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addStretch(0);
    layout->setContentsMargins(10,0,10,0);
    layout->setSpacing(0);
    setLayout(layout);

    setAutoExclusive(true);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    setCheckable(true);
    setFixedHeight(CustomListitem::itemHeight);
    setAutoDefault(false);
}

CustomListitem::CustomListitem(const QString &Text, const long long Identifier, QDate Date, const bool ErgentToTop, QWidget *parent) :
    QPushButton(parent),
    expDate(Date),
    ID(Identifier),
    string(""),
    exp(expiration::normal)
{
    label = new QLabel(Text);
    QFont Font = font();
    Font.setPointSize(fontSize);
    label->setFont(Font);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addStretch(0);
    layout->setContentsMargins(10,0,10,0);
    layout->setSpacing(0);
    setLayout(layout);

    setAutoExclusive(true);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    setCheckable(true);
    setFixedHeight(CustomListitem::itemHeight);
    setAutoDefault(false);

    compareWithDate(QDate::currentDate(), ErgentToTop);
}

CustomListitem::CustomListitem(const QString &Text, const QString &String, QWidget *parent) :
    QPushButton(parent),
    ID(-1),
    string(String),
    exp(expiration::normal)
{
    label = new QLabel(Text);
    QFont Font = font();
    Font.setPointSize(fontSize);
    label->setFont(Font);

    layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addStretch(0);
    layout->setContentsMargins(10,0,10,0);
    layout->setSpacing(0);
    setLayout(layout);

    setAutoExclusive(true);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    setCheckable(true);
    setFixedHeight(CustomListitem::itemHeight);
    setAutoDefault(false);
}

long long CustomListitem::getID()
{
    return ID;
}

void CustomListitem::setLabelText(QString NewText)
{
    label->setText(NewText);
}

void CustomListitem::setExpDate(QDate NewDate, const bool ErgentToTop)
{
    expDate = NewDate;
    compareWithDate(QDate::currentDate(), ErgentToTop);
}

expiration CustomListitem::getExp() const
{
    return exp;
}

void CustomListitem::setExp(expiration Exp)
{
    switch(Exp) {
    case expiration::irrelevant:
    case expiration::expired:
        setStyleSheet(WarningStyle);
        break;
    case expiration::alerting:
        setStyleSheet(AlertStyle);
        break;
    case expiration::highlighted:
        setStyleSheet(HighlightedStyle);
        break;
    default:
        setStyleSheet(NormalStyle);
    }
    this->exp = Exp;
}

void CustomListitem::compareWithDate(QDate Date, const bool ErgentToTop)
{
    if(expDate.isValid()) {

        long long difference = -expDate.daysTo(Date);

        if(difference < 0 && ErgentToTop) {
            setExp(expiration::expired);
        }
        else if(difference < 0 && !ErgentToTop) {
            setExp(expiration::irrelevant);
        }
        else if(difference <= 60) {
            setExp(expiration::alerting);
        }
        else {
            setExp(expiration::normal);
        }
    }
}

void CustomListitem::setUnExpirable()
{
    expDate = QDate();
}

QDate CustomListitem::getExpDate() const
{
    return expDate;
}

QString CustomListitem::getLabelText() const
{
    return label->text();
}

QString CustomListitem::toString() const
{
    return string;
}

bool CustomListitem::isExpirable() const
{
    return expDate.isValid();
}

CustomListitem::~CustomListitem()
{
    delete label;
    delete layout;
}

void CustomListitem::mouseDoubleClickEvent(QMouseEvent *)
{
    if(ID != -1) {
        emit doubleClicked(ID);
    }
}
