#include "ViewPicture.h"
#include "ui_ViewPicture.h"

ViewPicture::ViewPicture(QString Path, QWidget *parent) :
    QDialog(parent),
    path(Path),
    ui(new Ui::ViewPicture)
{
    ui->setupUi(this);
    QPixmap pixmap(path);
    ui->Picture->setPixmap(pixmap.scaled(width(),height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

ViewPicture::~ViewPicture()
{
    delete ui;
}
