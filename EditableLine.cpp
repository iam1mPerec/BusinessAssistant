#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "widgetLineEdit.h"
#include "EditableLine.h"
#include "statics.h"
#include "QCompleter"

EditableLine::EditableLine(QWidget* parent):
    EditableWidget (parent),
    isRequired(true)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    lineEdit = new widgetLineEdit(this);
    lineEdit->setStyleSheet(defaultStyle + "color: black; font-size: 18px; padding-left: 10px;");
    lineEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    lineEdit->hide();
    layout->addWidget(lineEdit);

    connect(lineEdit, &widgetLineEdit::focusLeft, this, &EditableLine::onFocusLost);
}

void EditableLine::setRequired(bool value)
{
    isRequired = value;
}

void EditableLine::startYearValidation()
{
    setYearValidator(this->lineEdit);
}

void EditableLine::setSelected(bool)
{
    if(!lineEdit->hasFocus()) {
        label->hide();
        lineEdit->show();
        lineEdit->setFocus();
        lineEdit->setText(label->text());
    }
}

QString EditableLine::getText() const
{
    return label->text();
}

void EditableLine::setAutoComplition(QStringList List)
{
    QCompleter *fileEditCompleter = new QCompleter(List, this);
    fileEditCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    this->lineEdit->setCompleter(fileEditCompleter);
}

void EditableLine::setText(QString text)
{
    label->setText(text);
}

void EditableLine::onFocusLost()
{
    label->show();
    lineEdit->hide();
    label->setText(lineEdit->text());

    emit focusOut();
}

EditableLine::~EditableLine()
{
    delete lineEdit;
}
