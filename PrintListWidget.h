#ifndef PRINTLISTWIDGET_H
#define PRINTLISTWIDGET_H

#include <QScrollArea>
class PrintListWidget : public QScrollArea
{
    Q_OBJECT
    static const int margin, spacing;
    QWidget * contents;
    QLayout * layout;
    QList<class PrintListItem*> items;

public:

    bool isChecked(long long ID);
    bool hasUnchecked();
    void setAllChecked(bool state);
    explicit PrintListWidget(QWidget *parent = nullptr);
    void addItem(class PrintListItem* Item);

};

#endif // PRINTLISTWIDGET_H
