#ifndef CUSTOMLISTITEM_H
#define CUSTOMLISTITEM_H

#include <QPushButton>
#include <QDate>
#include "EnumStates.h"
#include "EnumExpiration.h"

class CustomListitem : public QPushButton
{
    Q_OBJECT

    QDate expDate;
    long long ID;
    QString string;
    class QHBoxLayout * layout;
    class QLabel * label;
    expiration exp;

    static const int fontSize;
    static const int itemHeight;
    static const QString NormalStyle;
    static const QString AlertStyle;
    static const QString WarningStyle;
    static const QString HighlightedStyle;

public:

    CustomListitem( const QString& Text, const QString &Identifier , QWidget* parent = nullptr );
    CustomListitem( const QString& Text, const long long Identifier , QWidget* parent = nullptr );
    CustomListitem( const QString& Text, const long long Identifier , class QDate Date, const bool ErgentToTop, QWidget* parent = nullptr );
    long long getID();
    void setLabelText(QString NewText);
    void setExpDate(QDate NewDate, const bool ErgentToTop);
    void compareWithDate(QDate Date, const bool ErgentToTop);
    void setUnExpirable();
    class QDate getExpDate() const;
    QString getLabelText()    const;
    QString toString() const;
    bool isExpirable() const;
    expiration getExp() const;
    void setExp(expiration Exp);

    ~CustomListitem();

signals:
    void doubleClicked(long long ID);

protected:
    void mouseDoubleClickEvent(QMouseEvent *);

};

#endif // CUSTOMLISTITEM_H
