#ifndef PRINTFACILITY_H
#define PRINTFACILITY_H

#include <QDialog>

namespace Ui {
class PrintFacility;
}

class PrintFacility : public QDialog
{
    Q_OBJECT
    class Facility * facility;

public:
    explicit PrintFacility(class Facility* Facility, QWidget *parent = nullptr);
    ~PrintFacility();

private:
    Ui::PrintFacility *ui;
};

#endif // PRINTFACILITY_H
