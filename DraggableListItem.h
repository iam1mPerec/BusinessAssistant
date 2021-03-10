#ifndef DRAGGABLELISTITEM_H
#define DRAGGABLELISTITEM_H

#include<QPushButton>

class DraggableListItem : public QPushButton
{
    Q_OBJECT
    long long ID;
public:
    DraggableListItem(const QString& Text, const long long Identifier, QWidget* parent = nullptr);
};

#endif // DRAGGABLELISTITEM_H
