#include "pirate.h"
#include <iostream>

using namespace std;

void Pirate::print(ostream &os) const
{
    os << "Pirate ID: " << pirateId << ", Treasure: " << treasure << endl;
}

ostream &operator<<(ostream &os, const Pirate &pirate)
{
    pirate.print(os);
    return os;
}