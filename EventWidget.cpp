#include <QVBoxLayout>
#include "EventWidget.h"

EventWidget::EventWidget(QString Name, QString Description, QWidget *parent) :
    QFrame(parent)
{
    name        = new QLabel(Name);
    name->setStyleSheet("border: none;");
    description = new QLabel(Description);
    description->setStyleSheet("border: none;");
    arrow       = new QLabel;
    arrow->setStyleSheet("border: none;");

    arrow->setScaledContents(true);
    arrow->setPixmap(QPixmap(":/icons/down_arrow.png"));
    arrow->setFixedHeight(20);
    arrow->setFixedWidth(20);

    layout = new QVBoxLayout;
    arrowLayout = new QVBoxLayout;

    layout->addWidget(name);
    layout->addWidget(description);
    arrowLayout->addWidget(arrow);
    arrowLayout->setAlignment(Qt::AlignCenter);
    layout->addLayout(arrowLayout);

    layout->setSpacing(0);
    layout->setMargin(0);

    layout->setAlignment(Qt::AlignCenter);

    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    name->setAlignment(Qt::AlignCenter);

    description->hide();


    setStyleSheet("border: 1px solid gray;");
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    setLayout(layout);
    setFixedHeight(400);
}

void EventWidget::setName(QString NewName)
{
    name->setText(NewName);
}

void EventWidget::setDescription(QString NewDescription)
{
    description->setText(NewDescription);
}

EventWidget::~EventWidget()
{
    delete name;
    delete description;
    delete arrow;

    delete layout;
}

void EventWidget::mousePressEvent(QMouseEvent *event)
{
    description->setHidden(!description->isHidden());
    if(description->isHidden()) {
        arrow->setPixmap(QPixmap(":/icons/down_arrow.png"));
    }
    else {
        arrow->setPixmap(QPixmap(":/icons/up_arrow.png"));
    }
}
