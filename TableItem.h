#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QFrame>
#include <QDate>

class TableItem : public QFrame
{
    Q_OBJECT

    static QString selectedStyle;
    static QString layoutStyle;
    bool selected;
    class TableItemObserver * observer;

    QString color;
    QDate date;
    const int maxWorkers;
    class QHBoxLayout* layout;
    class QLabel* dateLabel;
    QList<class HoverableLabel*> labels;

public:
    TableItem(const QDate& Date, const int MaxWorkers, QWidget* Parent=nullptr);
    void setText(const int Field, QString Text);
    void setColor(const int Field, QString Color);
    void subscribe(class FacilityTable* subscriber);
    bool isFree(int space);
    bool hasPassage();
    void clear();
    QDate getDate();
    void setDate(QDate newDate);
    ~TableItem();

};

#endif // TABLEITEM_H
