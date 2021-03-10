#ifndef SETTINGS_H
#define SETTINGS_H


#include <QString>
#include "EnumFirm.h"

struct FirmSettings {
    QString directorName;
    QString directorSurname;
    QString address;
    QString zip;
    QString city;
    QString email;
    QString phone;
    QString fax;
    QString mobile;
    QString taxNumber;
    QString ustNumber;
    QString bank;
    QString blz;
    QString kto;
    QString iban;
    QString swift;
    QString schoolAddress;
    QString schoolTeacher;
    QString schoolLasts;
};

class Settings
{
    Settings();
    FirmSettings ELiD;
    FirmSettings ELiD_SP;
    QString hours;
    QString rate;

    static Settings* instance;

    FirmSettings const &getFirm(Firm Firm) const;
public:
    static Settings* getInstance();
    static void removeInstance();

    QString getDirectorName(const Firm Firm) const;
    QString getDirectorSurname(const Firm Firm) const;
    QString getAddress(const Firm Firm) const;
    QString getZip(const Firm Firm) const;
    QString getCity(const Firm Firm) const;
    QString getEmail(const Firm Firm) const;
    QString getPhone(const Firm Firm) const;
    QString getFax(const Firm Firm) const;
    QString getMobile(const Firm Firm) const;
    QString getTaxNumber(const Firm Firm) const;
    QString getUstNumber(const Firm Firm) const;
    QString getBank(const Firm Firm) const;
    QString getBlz(const Firm Firm) const;
    QString getKto(const Firm Firm) const;
    QString getIban(const Firm Firm) const;
    QString getSwift(const Firm Firm) const;
    QString getSchoolAddress(const Firm Firm) const;
    QString getSchoolTeacher(const Firm Firm) const;
    QString getSchoolLasts(const Firm Firm) const;

    QString getHours() const;
    QString getRate() const;

    void setDirectorName(const Firm Firm, const QString &value);
    void setDirectorSurname(const Firm Firm, const QString &value);
    void setAddress(const Firm Firm, const QString &value);
    void setZip(const Firm Firm, const QString &value);
    void setCity(const Firm Firm, const QString &value);
    void setEmail(const Firm Firm, const QString &value);
    void setPhone(const Firm Firm, const QString &value);
    void setFax(const Firm Firm, const QString &value);
    void setMobile(const Firm Firm, const QString &value);
    void setTaxNumber(const Firm Firm, const QString &value);
    void setUstNumber(const Firm Firm, const QString &value);
    void setBank(const Firm Firm, const QString &value);
    void setBlz(const Firm Firm, const QString &value);
    void setKto(const Firm Firm, const QString &value);
    void setIban(const Firm Firm, const QString &value);
    void setSwift(const Firm Firm, const QString &value);
    void saveToFile();
    void loadFromFile();

    void setHours(const QString &value);
    void setRate(const QString &value);
    void setSchoolAddress(const Firm Firm, const QString &value);
    void setSchoolTeacher(const Firm Firm, const QString &value);
    void setSchoolLasts(const Firm Firm, const QString &value);
};

void saveFirm(Firm Firm, const Settings &settings, QDataStream &stream);
void loadFirm(Firm Firm, Settings &settings, QDataStream &stream);
QDataStream &operator <<(QDataStream &stream, const Settings &settings);
QDataStream &operator >>(QDataStream &stream, Settings &settings);

#endif // SETTINGS_H
