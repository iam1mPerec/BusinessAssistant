#ifndef VIEWPICTURE_H
#define VIEWPICTURE_H

#include <QDialog>

namespace Ui {
class ViewPicture;
}

class ViewPicture : public QDialog
{
    Q_OBJECT
    QString path;

public:
    explicit ViewPicture(QString Path, QWidget *parent = nullptr);
    ~ViewPicture();

private:
    Ui::ViewPicture *ui;
};

#endif // VIEWPICTURE_H
