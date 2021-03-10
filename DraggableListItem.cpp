#include "DraggableListItem.h"

DraggableListItem::DraggableListItem(const QString& Text, const long long Identifier, QWidget* parent) :
QPushButton(parent),
ID(Identifier)
{
    setText(Text);
    setCheckable(true);
    setChecked(true);
}
