#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QList>
#include <QString>

class Document {

private:
    QString name;
    QString parentType;
    QList<QString> scans;
    class QDate* ExpirationDate;
    QString path;
    long long parentID;
    long long ID;
    long long scansID;

    static QString mainPath;
    static long long count;

public:
    Document(long long ParentID, QString ParentType);
    Document(long long ParentID, QString ParentType, long long PresetID, long long PresetScansID);

    void setName(QString NewName);
    void setDate(const QDate &NewDate);
    void setPath(const QString &value);
    void addScan(QString NewScan);
    void removeScan(const QString &ScanToRemove);
    void deleteScans();
    void copyScans(QList<QString> NewScans);
    void refactorScans(QList<QString> Scans);
    void resetScansID();
    void deleteTemp();

    QString getExstension(QString path) const;
    QString getName()               const;
    QDate getExpirationDate()       const;
    QString getPath()               const;
    long long getID()               const;
    long long getScansID()          const;
    QList<QString> getScans()       const;
    QList<QString> copyTemp()       const;


    ~Document();
    static long long getCount();
    static void setCount(long long value);
};

QDataStream &operator <<(QDataStream &stream, const Document &document);
QDataStream &operator >>(QDataStream &stream, Document &document);
bool dateComp(Document * a, Document * b);

#endif // DOCUMENT_H
