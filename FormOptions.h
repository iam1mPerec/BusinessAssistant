#ifndef FORMOPTIONS_H
#define FORMOPTIONS_H

#include <QDialog>

namespace Ui {
class FormOptions;
}

class FormOptions : public QDialog
{
    Q_OBJECT
    class Settings* settings;

public:
    explicit FormOptions(QWidget *parent = nullptr);
    void load();
    void save();
    ~FormOptions();

private:
    Ui::FormOptions *ui;
};

#endif // FORMOPTIONS_H
