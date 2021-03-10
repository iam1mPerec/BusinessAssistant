#ifndef PRINTLISTITEM_H
#define PRINTLISTITEM_H

#include <QFrame>


class PrintListItem : public QFrame
{
    Q_OBJECT
    class QHBoxLayout* layout;
    class QLabel* label;
    class QCheckBox* checkbox;
    long long id;

public:
    PrintListItem(QString Name, long long ID, QWidget* parent = nullptr);
    long long getID();
    void setChecked(bool state);
    bool isChecked();
    ~PrintListItem();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // PRINTLISTITEM_H
