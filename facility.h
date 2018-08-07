#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include <vector>

class Facility {

private:
    std::string phone;
    std::string address;
    std::vector<class worker*> workers;

public:
    Facility();
    Facility(std::string Address, std::string Phone);

    void setPhone(std::string NewPhone);
    void setAddress(std::string NewAddress);
    void addWorker(class worker *NewWorker);

    std::string getPhone()   const;
    std::string getAddress() const;

};

#endif // FACILITY_H
