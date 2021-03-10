#include "Settings.h"
#include "statics.h"

#include <QFile>
#include <qdatastream.h>

Settings * Settings::instance = nullptr;

Settings::Settings()
{

}

QString Settings::getRate() const
{
    return rate;
}

QString Settings::getHours() const
{
    return hours;
}

void Settings::setHours(const QString &value)
{
    this->hours = value;
}

void Settings::setRate(const QString &value)
{
    this->rate = value;
}

FirmSettings const &Settings::getFirm(Firm FIRM) const
{
    if(FIRM == Firm::ELID_SP) {
        return this->ELiD_SP;
    }
    return this->ELiD;
}

Settings *Settings::getInstance()
{
    if(instance == nullptr) {
        qDebug("instance created");
        instance = new Settings;
    }
    return instance;
}

void Settings::removeInstance()
{
    if(instance) {
        qDebug("instance removed");
        delete instance;
        instance = nullptr;
    }
}

QString Settings::getDirectorName(const Firm Firm) const
{
    return getFirm(Firm).directorName;
}

QString Settings::getDirectorSurname(const Firm Firm) const
{
    return getFirm(Firm).directorSurname;
}

QString Settings::getAddress(const Firm Firm) const
{
    return getFirm(Firm).address;
}

QString Settings::getZip(const Firm Firm) const
{
    return getFirm(Firm).zip;
}

QString Settings::getCity(const Firm Firm) const
{
    return getFirm(Firm).city;
}

QString Settings::getEmail(const Firm Firm) const
{
    return getFirm(Firm).email;
}

QString Settings::getPhone(const Firm Firm) const
{
    return getFirm(Firm).phone;
}

QString Settings::getFax(const Firm Firm) const
{
    return getFirm(Firm).fax;
}

QString Settings::getMobile(const Firm Firm) const
{
    return getFirm(Firm).mobile;
}

QString Settings::getTaxNumber(const Firm Firm) const
{
    return getFirm(Firm).taxNumber;
}

QString Settings::getUstNumber(const Firm Firm) const
{
    return getFirm(Firm).ustNumber;
}

QString Settings::getBank(const Firm Firm) const
{
    return getFirm(Firm).bank;
}

QString Settings::getBlz(const Firm Firm) const
{
    return getFirm(Firm).blz;
}

QString Settings::getKto(const Firm Firm) const
{
    return getFirm(Firm).kto;
}

QString Settings::getIban(const Firm Firm) const
{
    return getFirm(Firm).iban;
}

QString Settings::getSwift(const Firm Firm) const
{
    return getFirm(Firm).swift;
}

QString Settings::getSchoolTeacher(const Firm Firm) const
{
    return getFirm(Firm).schoolTeacher;
}

QString Settings::getSchoolAddress(const Firm Firm) const
{
    return getFirm(Firm).schoolAddress;
}

QString Settings::getSchoolLasts(const Firm Firm) const
{
    return getFirm(Firm).schoolLasts;
}

void Settings::setDirectorName(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.directorName = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.directorName = value;
        break;
        default:
        break;
    }
}

void Settings::setDirectorSurname(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.directorSurname = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.directorSurname = value;
        break;
        default:
        break;
    }
}

void Settings::setAddress(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.address = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.address = value;
        break;
        default:
        break;
    }
}

void Settings::setZip(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.zip = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.zip = value;
        break;
        default:
        break;
    }
}

void Settings::setCity(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.city = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.city = value;
        break;
        default:
        break;
    }
}

void Settings::setEmail(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.email = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.email = value;
        break;
        default:
        break;
    }
}

void Settings::setPhone(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.phone = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.phone = value;
        break;
        default:
        break;
    }
}

void Settings::setFax(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.fax = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.fax = value;
        break;
        default:
        break;
    }
}

void Settings::setMobile(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.mobile = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.mobile = value;
        break;
        default:
        break;
    }
}

void Settings::setTaxNumber(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.taxNumber = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.taxNumber = value;
        break;
        default:
        break;
    }
}

void Settings::setUstNumber(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.ustNumber = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.ustNumber = value;
        break;
        default:
        break;
    }
}

void Settings::setBank(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.bank = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.bank = value;
        break;
        default:
        break;
    }
}

void Settings::setBlz(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.blz = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.blz = value;
        break;
        default:
        break;
    }
}

void Settings::setKto(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.kto = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.kto = value;
        break;
        default:
        break;
    }
}

void Settings::setIban(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.iban = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.iban = value;
        break;
        default:
        break;
    }
}

void Settings::setSwift(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.swift = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.swift = value;
        break;
        default:
        break;
    }
}

void Settings::setSchoolTeacher(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.schoolTeacher = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.schoolTeacher = value;
        break;
        default:
        break;
    }
}

void Settings::setSchoolAddress(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.schoolAddress = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.schoolAddress = value;
        break;
        default:
        break;
    }
}

void Settings::setSchoolLasts(const Firm FIRM, const QString &value)
{
    switch(FIRM) {
        case Firm::ELID:
         this->ELiD.schoolLasts = value;
        break;
        case Firm::ELID_SP:
         this->ELiD_SP.schoolLasts = value;
        break;
        default:
        break;
    }
}

void Settings::saveToFile()
{
    if(instance) {
        createDirectory("save");
        QFile file("save/settings.txt");

        if(file.open(QIODevice::WriteOnly)) {

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_5_9);
            in << *this->instance;
        }
        file.flush();
        file.close();
    }
}

void Settings::loadFromFile()
{
    QFile settingsFile("save/settings.txt");
    if(settingsFile.open(QIODevice::ReadOnly)) {

        QDataStream out(&settingsFile);
        out.setVersion(QDataStream::Qt_5_9);
        out>>*instance;
    }
    settingsFile.close();
}

QDataStream &operator <<(QDataStream &stream, const Settings &settings)
{
    saveFirm(Firm::ELID, settings, stream);
    saveFirm(Firm::ELID_SP, settings, stream);

    stream << settings.getHours();
    stream << settings.getRate();

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Settings &settings)
{
    loadFirm(Firm::ELID, settings, stream);
    loadFirm(Firm::ELID_SP, settings, stream);

    QString TempString;

    stream >> TempString;
    settings.setHours(TempString);
    stream >> TempString;
    settings.setRate(TempString);

    return stream;
}

void saveFirm(Firm Firm, const Settings &settings, QDataStream &stream)
{
    stream << settings.getDirectorName(Firm);
    stream << settings.getDirectorSurname(Firm);
    stream << settings.getAddress(Firm);
    stream << settings.getZip(Firm);
    stream << settings.getCity(Firm);
    stream << settings.getEmail(Firm);
    stream << settings.getPhone(Firm);
    stream << settings.getFax(Firm);
    stream << settings.getMobile(Firm);
    stream << settings.getTaxNumber(Firm);
    stream << settings.getUstNumber(Firm);
    stream << settings.getBank(Firm);
    stream << settings.getBlz(Firm);
    stream << settings.getKto(Firm);
    stream << settings.getIban(Firm);
    stream << settings.getSwift(Firm);
    stream << settings.getSchoolAddress(Firm);
    stream << settings.getSchoolTeacher(Firm);
    stream << settings.getSchoolLasts(Firm);
}

void loadFirm(Firm Firm, Settings &settings, QDataStream &stream)
{
    QString TempString;

    stream >> TempString;
    settings.setDirectorName(Firm, TempString);
    stream >> TempString;
    settings.setDirectorSurname(Firm, TempString);
    stream >> TempString;
    settings.setAddress(Firm, TempString);
    stream >> TempString;
    settings.setZip(Firm, TempString);
    stream >> TempString;
    settings.setCity(Firm, TempString);
    stream >> TempString;
    settings.setEmail(Firm, TempString);
    stream >> TempString;
    settings.setPhone(Firm, TempString);
    stream >> TempString;
    settings.setFax(Firm, TempString);
    stream >> TempString;
    settings.setMobile(Firm, TempString);
    stream >> TempString;
    settings.setTaxNumber(Firm, TempString);
    stream >> TempString;
    settings.setUstNumber(Firm, TempString);
    stream >> TempString;
    settings.setBank(Firm, TempString);
    stream >> TempString;
    settings.setBlz(Firm, TempString);
    stream >> TempString;
    settings.setKto(Firm, TempString);
    stream >> TempString;
    settings.setIban(Firm, TempString);
    stream >> TempString;
    settings.setSwift(Firm, TempString);
    stream >> TempString;
    settings.setSchoolAddress(Firm, TempString);
    stream >> TempString;
    settings.setSchoolTeacher(Firm, TempString);
    stream >> TempString;
    settings.setSchoolLasts(Firm, TempString);
}
