#ifndef EDITABLETEXT_H
#define EDITABLETEXT_H

#include "EditableWidget.h"

class EditableText : public EditableWidget
{
    class widgetTextEdit* textEdit;
public:
    void setText(QString Text);
    EditableText(QWidget* parent=nullptr);

    void setSelected(bool);

    QString getText() const;

    ~EditableText();


private slots:

    void onFocusLost();

};

#endif // EDITABLETEXT_H
