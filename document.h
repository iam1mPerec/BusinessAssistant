#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Document {

private:
    std::string name;
    std::vector<std::string> scans;
    class Date* ExpirationDate;

public:
    Document();
    Document(std::string Name, class Date LicenseExpirationDate);

    void setName(std::string NewName);
    void setDate(const Date &NewDate);
    void addScan(const std::string &NewScan);

    int getDaysToExpiration() const;

    std::string getName() const;

    ~Document();
};

#endif // DOCUMENT_H
