#include <iostream>
#include "worker.h"

Worker::Worker()
{
}

Worker::Worker(std::string Name, std::string Surname, std::string Phone) :
name(Name),
surname(Surname),
phone(Phone)
{
}
