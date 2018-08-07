#include "facility.h"
#include "worker.h"


Facility::Facility() {

}
Facility::Facility(std::string Address, std::string Phone):
phone(Phone),
address(Address)
{

}

void Facility::setPhone(std::string NewPhone) {
    this->phone = NewPhone;
}
void Facility::setAddress(std::string NewAddress) {
    this->address = NewAddress;
}
void Facility::addWorker(worker *NewWorker) {
    this->workers.push_back(NewWorker);
}

std::string Facility::getPhone() const {
    return this->phone;
}
std::string Facility::getAddress() const {
    return this->address;
}
