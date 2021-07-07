#include <QMouseEvent>
#include "ClickablePicture.h"
#include "ViewPicture.h"

ClickablePicture::ClickablePicture(QWidget *parent) :
QLabel(parent)
{

}

void ClickablePicture::setPath(const QString &Path)
{
    path = Path;
    QPixmap pixmap(path);
    setPixmap(pixmap.scaled(width(), height(), Qt::KeepAspectRatio));
}

QString ClickablePicture::getPath() const
{
    return path;
}

void ClickablePicture::mousePressEvent(QMouseEvent*)
{
    if(!path.isEmpty()) {
        ViewPicture window(path, this);
        window.setModal(true);
        window.exec();
    }
}
