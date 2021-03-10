#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include "EnumFirm.h"

class Company
{
    QString name;
    QString surname;
    QString address;
    QString zip;
    QString city;
    Firm firm;


public:
    Company();

    QString getName() const;
    QString getSurname() const;
    QString getAddress() const;
    QString getZip() const;
    QString getCity() const;
    Firm getFirm() const;

    void setName(const QString &value);
    void setSurname(const QString &value);
    void setAddress(const QString &value);
    void setZip(const QString &value);
    void setCity(const QString &value);
    void setFirm(const Firm &value);
};

#endif // COMPANY_H
