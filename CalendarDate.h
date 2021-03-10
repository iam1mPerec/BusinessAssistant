#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include "EnumDateType.h"

struct DateState {
    static const QString baseStyle;
    static const QString CheckedStyle;
    static const QString UnCheckedStyle;
    static const QString DisabledStyle;

    DateTypes type;
    bool disabled;
    bool checked;
    bool event;

    void resetState();
    void disable();
    void toggleChecked();
    void unCheck();
    void setChecked(bool Checked);

    QString getBaseStyle();
    QString getPixMap();

    bool isChecked() const;
    bool isDisabled() const;

    void setState(bool eventPresent);
    void setState(DateTypes Type);

public:
    DateState();
    DateTypes getType() const;
};

class CalendarDate : public QLabel
{
    Q_OBJECT

    static int count;
    static const int ButtonSize;

    DateState state;

    class QDate* date;
    const int ID;

    class QGridLayout *DateLayout;
    QLabel *DateLabel;

    class CalendarDateObserver* observer;

public:

    static int getButtonSize();
    static void setCount(int presetCount);
    static void resetCount();

    void setState(bool eventPresent);
    void setState(DateTypes Type);

    void toDefault();
    void addObserver(class CalendarDateObserver *Sub);
    void disable();
    void diselect();
    void setChecked(bool Checked);
    void simmulateClicked();
    explicit CalendarDate(QWidget* parent=nullptr);
    void setDate(QDate Date);
    bool compareDates(const QDate &AnotherDate) const;
    bool isDisabled() const;
    int getID() const;
    class QDate getDate() const;
    ~CalendarDate();

signals:

    void clicked();

protected:

    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
