#ifndef VIEWEVENT_H
#define VIEWEVENT_H

#include <QDialog>

namespace Ui {
class ViewEvent;
}

class ViewEvent : public QDialog
{
    Q_OBJECT
    class Event* event;

public:
    explicit ViewEvent(Event* Event, QWidget *parent = nullptr);
    ~ViewEvent();

private slots:
    void on_cansel_clicked();

    void on_save_clicked();

private:
    Ui::ViewEvent *ui;
};

#endif // VIEWEVENT_H
