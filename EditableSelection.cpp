#include "EditableSelection.h"
#include <QRadioButton>
#include <QWidget>
#include "Widget.h"
#include <QHBoxLayout>
#include "QLabel"
#include "QDebug"

EditableSelection::EditableSelection(QWidget* parent) :
    EditableWidget(parent),
    selectionWidget(nullptr),
    selectionLayout(nullptr)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    this->selectionWidget = new QWidget;
    this->selectionLayout = new QHBoxLayout;
    this->selectionWidget->setLayout(selectionLayout);
    this->selectionWidget->hide();
    this->layout->addWidget(this->selectionWidget);
    this->layout->setAlignment(Qt::AlignLeft);
    this->selectionLayout->setSpacing(40);
    this->selectionLayout->setMargin(0);
}

void EditableSelection::setSelection(QList<QString> Selection)
{
    for(auto item : Selection) {
        appendSelection(item);
    }
}

void EditableSelection::appendSelection(QString Selection)
{
    Widget * button = new Widget(Selection, this);

    QFont font = button->font();
    font.setPointSize(12);
    button->setFont(font);

    this->selectionLayout->addWidget(button);
    this->selectionWidgets.append(button);
    connect(button, &Widget::clicked, this, &EditableSelection::onSelection);
    connect(button, &Widget::focusLeft, this, &EditableSelection::onFocusLost);
}

void EditableSelection::select(QString Selection)
{
    for(auto item : this->selectionWidgets) {
        if(item->text() == Selection) {
            item->setChecked(true);
            this->label->setText(item->text());
        }
    }
}

void EditableSelection::select(const int Selection)
{
    this->selectionWidgets[Selection]->setChecked(true);
    this->label->setText(this->selectionWidgets[Selection]->text());
}

QString EditableSelection::getText() const
{
    for (auto item : selectionWidgets) {
        if(item->isChecked()) {
            return item->text();
        }
    }
    return "";
}

int EditableSelection::getValue() const
{
    for(int i = 0; i < this->selectionWidgets.length(); i++) {
        if(this->selectionWidgets[i]->text() == this->label->text()) {
            return i + 1;
        }
    }
    return -1;
}

void EditableSelection::setSelected(bool)
{
    this->label->hide();
    this->selectionWidget->show();
    if(selectionWidgets.length()) {
        selectionWidgets[0]->setFocus();
    }
}


EditableSelection::~EditableSelection()
{
    for(auto item : selectionWidgets) {
        delete item;
    }
    delete selectionLayout;
    delete selectionWidget;
}

void EditableSelection::onFocusLost()
{
    bool noFocus = true;
    for(auto radioButton : selectionWidgets) {
        if(radioButton->hasFocus()) {
            noFocus = false;
        }
    }
    if(noFocus) {
        label->setText(getText());
        label->show();

        this->selectionWidget->hide();
    }
}

void EditableSelection::onSelection()
{
    parentWidget()->setFocus();
    label->setText(getText());
    label->show();

    this->selectionWidget->hide();
}
