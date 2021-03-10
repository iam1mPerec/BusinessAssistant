#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

class CustomButton : public QPushButton
{
    Q_OBJECT

    class QVariantAnimation* transition;
    QColor currentColor;
    int duration;

public:
    CustomButton(QWidget* parent = nullptr);
    bool event(QEvent *event);
    void animateHover(bool in);
    void setTransitionDuration(int Duration);
    void paintEvent(QPaintEvent * event);
};

#endif // CUSTOMBUTTON_H
