#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QWidget>
#include <QScrollArea>

class CustomListWidget : public QScrollArea
{
    Q_OBJECT
    QLayout *documentsListLayout;
    QWidget *widget;

    void createItem     (QWidget * widget);

public:
    explicit CustomListWidget(QWidget *parent = nullptr);
    void addItem        (QWidget * widget);
    void addAlertItem   (QWidget * widget);
    void addDangerItem  (QWidget * widget);
    void addArchivedItem(QWidget * widget);

signals:

public slots:
};

#endif // CUSTOMLISTWIDGET_H
