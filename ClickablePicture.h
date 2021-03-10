#ifndef CLICKABLEPICTURE_H
#define CLICKABLEPICTURE_H

#include <QLabel>

class ClickablePicture : public QLabel
{
    Q_OBJECT
    QString path;
public:

    ClickablePicture(QWidget *parent);

    void setPath(const QString &value);

    QString getPath() const;

signals:

protected:

    void mousePressEvent(QMouseEvent* event);

public slots:
};

#endif // CLICKABLEPICTURE_H
