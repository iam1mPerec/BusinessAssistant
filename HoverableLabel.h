#ifndef HOVERABLELABEL_H
#define HOVERABLELABEL_H

#include <QLabel>
#include <QDate>

class HoverableLabel : public QLabel
{
    Q_OBJECT

    static QString selectedStyle;
    static QString layoutStyle;

    bool isSelected;
    class TableItemObserver * observer;
    QString color;
    QDate date;

public:
    HoverableLabel(QDate Date, QWidget *parent);
    void toDefaultStyle();
    void setColor(QString Color);
    void setSelected(bool Selected);
    bool isFree();
    void subscribe(class FacilityTable* subscriber);
    void labelHovered(const int labelNumber);
    void setDate(QDate newDate);
    ~HoverableLabel();

protected:
    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);
};


#endif // HOVERABLELABEL_H
