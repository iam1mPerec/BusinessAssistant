#include <iostream>
#include "document.h"
#include "date.h"

Document::Document() :
ExpirationDate(nullptr)
{
    std::cout<<"New Date object has been created\n";
    std::cout<<"**********\n";
}

Document::Document(std::string Name, class Date LicenseExpirationDate):
    name(Name)
{
    this->ExpirationDate = new Date(LicenseExpirationDate);
    std::cout<<"New Date object has been created\n";
    std::cout<<"**********\n";
}

void Document::addScan(const std::string &NewScan) {
    this->scans.push_back(NewScan);
}

int Document::getDaysToExpiration() const {
    return ExpirationDate->getDaysToExpiration();
}

void Document::setName(std::string NewName) {
    this->name = NewName;
}

void Document::setDate(const Date &NewDate) {
    delete  this->ExpirationDate;
    this->ExpirationDate = new Date(NewDate);
}

std::string Document::getName() const {
    return this->name;
}

Document::~Document() {
    delete this->ExpirationDate;
    std::cout<<"Date object has been freed\n";
    std::cout<<"**********\n";
}
