#ifndef NEWEVENT_H
#define NEWEVENT_H

#include <QDialog>

namespace Ui {
class NewEvent;
}

class NewEvent : public QDialog
{
    Q_OBJECT

public:
    explicit NewEvent(class Event *event, QWidget *parent = nullptr);
    ~NewEvent();

private slots:
    void on_cansel_clicked();

    void on_save_clicked();

private:
    Ui::NewEvent *ui;
    class Event *event;
};

#endif // NEWEVENT_H
