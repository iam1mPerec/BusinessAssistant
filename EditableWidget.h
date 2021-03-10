#ifndef EDITABLELABEL_H
#define EDITABLELABEL_H

#include <QWidget>

class EditableWidget : public QWidget
{
    Q_OBJECT

protected:
    class EditableWidgetObserver* observer;
    class QLabel* label;
    class QVBoxLayout* layout;

    QString defaultStyle;
    QString color;
    int width, height;

public:
    void subscribe(EditableWidgetObserver* Observer);
    EditableWidget(QWidget* parent=nullptr);
    void setFontSize(const int value);
    void setFontSize(const int value, const bool isBold);
    void setColor(QString Color);
    void alignLabel(Qt::Alignment alignment);
    void sizeLabel(const QSizePolicy::Policy horisontal, const QSizePolicy::Policy vertical);
    void whiten();
    void deWhiten();
    virtual void setSelected(bool selected);
    bool event(QEvent *event);
    ~EditableWidget();

signals:
    void focusOut();
};

#endif // EDITABLELABEL_H
