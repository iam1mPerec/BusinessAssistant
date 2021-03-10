#ifndef EDITABLINE_H
#define EDITABLINE_H

#include "EditableWidget.h"

class EditableLine : public EditableWidget
{
    class widgetLineEdit* lineEdit;
    bool isRequired;

public:
    EditableLine(QWidget* parent=nullptr);
    void setText(QString text);
    void setSelected(bool);
    QString getText() const;
    void setAutoComplition(QStringList List);

    void setRequired(bool value);
    void startYearValidation();

    ~EditableLine();

private slots:

    void onFocusLost();
};

#endif // EDITABLINE_H
