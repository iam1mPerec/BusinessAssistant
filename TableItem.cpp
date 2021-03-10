#include <QHBoxLayout>
#include <QLocale>
#include <QLabel>
#include <QHoverEvent>
#include "TableItemObserver.h"
#include "HoverableLabel.h"
#include "TableItem.h"
#include <QDebug>

QString TableItem::selectedStyle = "padding: 3px; background-color: goldenrod; color:white;";
QString TableItem::layoutStyle = "padding: 1px; font-size: 9px; font-weight: bold;";

TableItem::TableItem(const QDate& Date, const int MaxWorkers, QWidget* Parent) :
    QFrame(Parent),
    selected(false),
    observer(nullptr),
    color(""),
    date(Date),
    maxWorkers(MaxWorkers)
{
    observer = new TableItemObserver();
    setMouseTracking(true);

    setStyleSheet("background-color: black;");
    layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(1);

    dateLabel = new QLabel("");

    dateLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dateLabel->setMinimumWidth(40);
    layout->addWidget(dateLabel);

    for (int i = 0; i < maxWorkers; i++) {
        HoverableLabel * textLabel = new HoverableLabel(this->date, this);
        labels.push_back(textLabel);
        textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(textLabel);
    }

    setDate(Date);

    setLayout(layout);
}

QDate TableItem::getDate() {
    return date;
}

void TableItem::setDate(QDate newDate)
{
    date = newDate;

    QLocale LocalName = QLocale::German;
    QString DayFormat   = "d ddd";

    if(date.isValid()) {
        QString labelText = LocalName.toString(date, DayFormat);
        labelText = labelText.left(labelText.length() - 1);
        dateLabel->setText(labelText);
    }
    else {
        dateLabel->setText("");
    }

    switch(date.dayOfWeek()) {
        case 6:
        dateLabel->setStyleSheet(layoutStyle + "background-color: lightgray;");
        break;
        case 7:
        dateLabel->setStyleSheet(layoutStyle + "background-color: gray;");
        break;
        default:
        dateLabel->setStyleSheet(layoutStyle + "background-color: white;");
        break;
    }

    for(auto label : this->labels) {
        label->setDate(this->date);
    }
}

void TableItem::setText(const int Field, QString Text) {
    labels[Field]->setText(Text);
}

void TableItem::setColor(const int Field, QString Color)
{
    labels[Field]->setColor(Color);
}

void TableItem::subscribe(FacilityTable *subscriber)
{
    observer->subscribe(subscriber);
}

bool TableItem::isFree(int space)
{
    return labels[space]->isFree();
}

bool TableItem::hasPassage()
{
    for(auto item : labels) {
        if(item->isFree()) {
            return true;
        }
    }
    return false;
}

void TableItem::clear()
{
    for(auto item : labels) {
        item->setColor("");
        item->setText("");
    }
}



TableItem::~TableItem()
{
    for(auto label : labels) {
        delete label;
    }
    delete observer;
}
