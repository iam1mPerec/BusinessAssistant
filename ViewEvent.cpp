#include <QMessageBox>
#include "ViewEvent.h"
#include "ui_ViewEvent.h"
#include "event.h"
#include "statics.h"

ViewEvent::ViewEvent(Event *Event, QWidget *parent) :
    QDialog(parent),
    event(Event),
    ui(new Ui::ViewEvent)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui->Name->setText(event->getName());
    ui->Description->setText(event->getDescription());
    ui->BeginsOnDate->setDate(event->getBeginsOnDate());
    ui->EndsOnDate->setDate(event->getEndsOnDate());
    ui->isRecurring->setChecked(event->getIsRecurring());
}

ViewEvent::~ViewEvent()
{
    delete ui;
}

void ViewEvent::on_cansel_clicked()
{
    close();
}

void ViewEvent::on_save_clicked()
{
    ui->save->setFocus();
    event->setName(ui->Name->getText());
    event->setDescription(ui->Description->getText());
    event->setBeginsOn(ui->BeginsOnDate->getDate());
    event->setEndsOn(ui->EndsOnDate->getDate());
    event->setIsRecurring(ui->isRecurring->isChecked());
    close();
}
