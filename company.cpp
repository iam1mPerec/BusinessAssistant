#include "company.h"

Firm Company::getFirm() const
{
    return firm;
}

void Company::setFirm(const Firm &value)
{
    firm = value;
}

Company::Company()
{

}

QString Company::getName() const
{
    return name;
}

void Company::setName(const QString &value)
{
    name = value;
}

QString Company::getSurname() const
{
    return surname;
}

void Company::setSurname(const QString &value)
{
    surname = value;
}

QString Company::getAddress() const
{
    return address;
}

void Company::setAddress(const QString &value)
{
    address = value;
}

QString Company::getZip() const
{
    return zip;
}

void Company::setZip(const QString &value)
{
    zip = value;
}

QString Company::getCity() const
{
    return city;
}

void Company::setCity(const QString &value)
{
    city = value;
}
