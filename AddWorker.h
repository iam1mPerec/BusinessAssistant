#ifndef ADDWORKER_H
#define ADDWORKER_H

#include <QDialog>

namespace Ui {
class AddWorker;
}

class AddWorker : public QDialog
{
    Q_OBJECT

public:
    explicit AddWorker(QWidget *parent = nullptr);
    ~AddWorker();

private:
    Ui::AddWorker *ui;
};

#endif // ADDWORKER_H
