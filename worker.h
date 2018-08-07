#ifndef WORKER_H
#define WORKER_H

#include <string>

class Worker {

    std::string name;
    std::string surname;
    std::string phone;
    class Facility* assignedFacility;

public:
    Worker();
    Worker(std::string Name, std::string Surname, std::string Phone);
};

#endif // WORKER_H
