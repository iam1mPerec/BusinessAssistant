#ifndef EVENTWIDGET_H
#define EVENTWIDGET_H

#include <QLabel>

class EventWidget : public QFrame
{
    Q_OBJECT

    class QVBoxLayout * layout;
    class QVBoxLayout * arrowLayout;

    class QLabel * name;
    class QLabel * description;
    class QLabel * arrow;

public:
    explicit EventWidget(QString Name, QString Description, QWidget *parent = nullptr);

    void setName(QString NewName);
    void setDescription(QString NewDescription);

    ~EventWidget();

protected:
    void mousePressEvent(QMouseEvent* event);

signals:

public slots:
};

#endif // EVENTWIDGET_H
