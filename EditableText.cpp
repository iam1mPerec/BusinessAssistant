#include <QLabel>
#include <QPushButton>
#include "widgetTextEdit.h"
#include <QHBoxLayout>
#include "EditableText.h"


EditableText::EditableText(QWidget* parent) :
EditableWidget (parent)
{
    textEdit = new widgetTextEdit;
    textEdit->setStyleSheet(defaultStyle + "color: black;");
    textEdit->hide();
    layout->addWidget(textEdit);
    label->setAlignment(Qt::AlignBaseline);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    label->setWordWrap(true);

    connect(textEdit, &widgetTextEdit::focusLeft, this, &EditableText::onFocusLost);


}

void EditableText::setSelected(bool)
{
    if(!textEdit->hasFocus()) {
        label->hide();
        textEdit->show();
        textEdit->setFocus();
        textEdit->setText(label->text());
        repaint();
    }
}

QString EditableText::getText() const
{
    return label->text();
}

void EditableText::setText(QString Text)
{
    label->setText(Text);
}

EditableText::~EditableText()
{
    delete textEdit;

}

void EditableText::onFocusLost()
{
    label->show();
    textEdit->hide();
    label->setText(textEdit->toPlainText());
    repaint();
}
