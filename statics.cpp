#include "statics.h"
#include <QWidget>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QString>
#include <QLineEdit>
#include <QDebug>
#include <QDate>
#include <QRegExp>
#include <QIntValidator>
#include <QDir>
#include <EditableWidget.h>

const int OLDESTYEAR = 1900;
const int NEWESTYEAR = 2100;

QString getErrorStyle()
{
    return "border: 2px solid red; color: black;";
}

bool isANumber(const QString &String)
{
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(String)) {
        return true;
    }
    return false;
}

bool isValidEnum(const Sex value)
{
    return value != Sex::none;
}

bool isValidEnum(const Firm value)
{
    return value != Firm::none;
}

bool isValidEnum(const MaritalStatus value)
{
    return value != MaritalStatus::none;
}

bool isValidDate(QLineEdit *YEAR, QLineEdit *MONTH, QLineEdit *DAY)
{
    QString dayStyle   = DAY->styleSheet();
    QString monthStyle = MONTH->styleSheet();
    QString yearStyle  = YEAR->styleSheet();

    if(!DAY->text().isEmpty() && !MONTH->text().isEmpty() && !YEAR->text().isEmpty() && YEAR->text().toInt() >= OLDESTYEAR && YEAR->text().toInt() <= NEWESTYEAR && QDate::isValid(YEAR->text().toInt(), MONTH->text().toInt(), DAY->text().toInt()))
    {
        DAY->setStyleSheet(dayStyle);
        DAY->repaint();
        MONTH->setStyleSheet(monthStyle);
        MONTH->repaint();
        YEAR->setStyleSheet(yearStyle);
        YEAR->repaint();
        return true;
    }
    else {

        if(!isANumber(DAY->text()) || DAY->text().isEmpty()) {
            DAY->setStyleSheet(DAY->styleSheet() + getErrorStyle());
            DAY->repaint();
        }

        if(!isANumber(MONTH->text()) || MONTH->text().isEmpty()) {
            MONTH->setStyleSheet(MONTH->styleSheet() + getErrorStyle());
            MONTH->repaint();
        }

        if(!isANumber(YEAR->text()) || YEAR->text().isEmpty() || YEAR->text().toInt() >= OLDESTYEAR || YEAR->text().toInt() <= NEWESTYEAR ) {
            YEAR->setStyleSheet(YEAR->styleSheet() + getErrorStyle());
            YEAR->repaint();
        }

        return false;
    }
}

bool isValidText(QLineEdit *TextField)
{
    if(!TextField->text().isEmpty()) {
        TextField->setStyleSheet("color: black;");
        TextField->repaint();
        return true;
    }
    else {
        TextField->setStyleSheet(getErrorStyle());
        TextField->repaint();
        return false;
    }
}

bool isValidNumber(QLineEdit *Number)
{
    if(!Number->text().isEmpty() && isANumber(Number->text())) {
        Number->setStyleSheet("color: black");
        Number->repaint();
        return true;
    }
    else {
        Number->setStyleSheet(getErrorStyle());
        Number->repaint();
        return false;
    }
}

void createDirectory(const QString &Path)
{
    if(!QDir(Path).exists()) {
        QDir().mkpath(Path);
    }
}

QString formatDate(int date)
{
    return QString("%1").arg(date, 2, 10, QChar('0'));
}

void setDayValidator(QLineEdit *Date)
{
    QRegExp rx("([1-9]|[12][0-9]|3[01])");
    QValidator *DayValidator = new QRegExpValidator(rx);
    Date->setValidator(DayValidator);
}

void setMonthValidator(QLineEdit *Date)
{
    QRegExp rx("([1-9]|1[0-2])");
    QValidator *DayValidator = new QRegExpValidator(rx);
    Date->setValidator(DayValidator);
}

void setYearValidator(QLineEdit *Date)
{
    QRegExp rx("[" + QString::number(OLDESTYEAR) + "-" + QString::number(NEWESTYEAR) + "]");
    QValidator *DayValidator = new QIntValidator(OLDESTYEAR, NEWESTYEAR);
    Date->setValidator(DayValidator);
}

void setNumberValidator(QLineEdit *Number)
{
    QValidator *NumberValidator = new QIntValidator(1, 99);
    Number->setValidator(NumberValidator);
}

void Whiten(QList<EditableWidget*> list) {
    for(auto item : list) {
        item->whiten();
    }
}

void deWhiten(QList<EditableWidget*> list) {
    for(auto item : list) {
        item->deWhiten();
    }
}



void printWidget(QWidget* widget, QWidget* parent)
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, parent);

    if (printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter;
        painter.begin(&printer);

        double xscale = printer.pageRect().width() / double(widget->width());
        double yscale = printer.pageRect().height() / double(widget->height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                           0);
        painter.scale(scale, scale);
        painter.translate(-widget->width()/2, 0);


        widget->render(&painter);
        painter.end();
    }
}
