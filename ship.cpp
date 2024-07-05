#include "ship.h"
#include <iostream>

using namespace std;

void Ship::print(ostream &os) const
{
    os << "Ship ID: " << shipId << ", Cannon Amount: " << cannon_count << endl;
}

ostream &operator<<(ostream &os, const Ship &ship)
{
    ship.print(os);
    return os;
}