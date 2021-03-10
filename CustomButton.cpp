#include <QEvent>
#include <QVariantAnimation>
#include <QStylePainter>
#include <QStyleOptionButton>
#include "CustomButton.h"

CustomButton::CustomButton(QWidget *parent):
    QPushButton(parent),
    duration(300)
{

}

bool CustomButton::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        qDebug("Entered");
        animateHover(true);
        break;
    case QEvent::HoverLeave:
        qDebug("Escaped!");
        animateHover(false);
        break;
    default:
        break;
    }

    return QPushButton::event(event);
}

void CustomButton::animateHover(bool in)
{
    const QColor &baseColor(palette().brush(QPalette::Button).color());
    const QColor &highlightColor(palette().brush(QPalette::Highlight).color());
    QColor startValue(in ? baseColor : highlightColor);

    if (transition) {
        startValue = transition->currentValue().value<QColor>();
        transition->stop();
    }

    transition = new QVariantAnimation(this);

    transition->setStartValue(startValue);
    transition->setEndValue(in ? highlightColor : baseColor);
    transition->setDuration(duration);

    connect(transition, &QVariantAnimation::valueChanged, [this](const QVariant &value){
        currentColor = value.value<QColor>();
        repaint();
    });

    connect(transition, &QVariantAnimation::destroyed, [this](){
        transition = nullptr;
    });

    transition->start(QAbstractAnimation::DeleteWhenStopped);
}

void CustomButton::setTransitionDuration(int Duration)
{
    duration = Duration;
}

void CustomButton::paintEvent(QPaintEvent * /*event*/)
{
    QStylePainter painter(this);
    QStyleOptionButton option;
    QPalette p(palette());

    initStyleOption(&option);

    p.setBrush(QPalette::Button, currentColor);

    option.palette = p;
    option.state |= QStyle::State_MouseOver;

    painter.drawControl(QStyle::CE_PushButton, option);
}
