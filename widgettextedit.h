#ifndef WIDGETTEXTEDIT_H
#define WIDGETTEXTEDIT_H

#include <QTextEdit>

class widgetTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit widgetTextEdit(QWidget *parent = nullptr);
    void focusOutEvent( QFocusEvent* event);

signals:
    void focusLeft();


signals:

public slots:
};

#endif // WIDGETTEXTEDIT_H
