#ifndef DRAGGABLELISTWIDGET_H
#define DRAGGABLELISTWIDGET_H

#include <QScrollArea>

class DraggableListWidget : public QScrollArea
{
    Q_OBJECT
    static const int margin, spacing;
    class QWidget * contents;
    QLayout * baseLayout;
    QList<class DraggableListItem*> items;
public:
    DraggableListWidget(QWidget *parent = nullptr);
    void addItem(DraggableListItem* Item);
};

#endif // DRAGGABLELISTWIDGET_H
