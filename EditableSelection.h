#ifndef EDITABLESELECTION_H
#define EDITABLESELECTION_H

#include "EditableWidget.h"

class EditableSelection : public EditableWidget
{
    QList<class QRadioButton*> selectionWidgets;
    class QWidget* selectionWidget;
    class QHBoxLayout* selectionLayout;
public:
    EditableSelection(QWidget* parent);
    void setSelection(QList<QString> Selection);
    void appendSelection(QString Selection);
    void select(const QString Selection);
    void select(const int Selection);
    void setSelected(bool);
    QString getText() const;
    int getValue() const;

    ~EditableSelection();

private slots:

    void onFocusLost();
    void onSelection();
};

#endif // EDITABLESELECTION_H
