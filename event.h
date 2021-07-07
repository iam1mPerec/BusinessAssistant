#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDate>

class Event
{
    static long long count;
    QDate beginsOn;
    QDate endsOn;
    QString name;
    QString description;
    bool isRecurring;
    long long ID;

public:
    Event();
    Event ( const Event& ) = default;
    Event(long long PresetID);

    void setBeginsOn(const QDate &value);
    void setEndsOn(const QDate &value);
    void setName(const QString &value);
    void setDescription(const QString &value);
    void setIsRecurring(bool value);

    QDate getBeginsOnDate()     const;
    QDate getEndsOnDate()     const;
    QDate getNextDate() const;
    bool isRelevant(const QDate &Date) const;
    bool getIsRecurring() const;
    QString toString()          const;
    QString getName()           const;
    QString getDescription()    const;
    long long getID()           const;
};

QDataStream &operator <<(QDataStream &stream, const Event &event);
QDataStream &operator >>(QDataStream &stream, Event &event);

#endif // EVENT_H
