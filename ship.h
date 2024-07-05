#ifndef SHIPS_H
#define SHIPS_H

#include <memory>
#include "pirates24b1.h"
#include "wet1util.h"
#include "ship.h"

using namespace std;

class Pirate;

class Ship
{
public:
    Ship(int id, int cannons) : shipId(id), cannon_count(cannons),
                                pirate_count(0), left_son(nullptr), right_son(nullptr), father(),
                                first(), last(), money_root()
    {
    }

    ~Ship()
    {
    }

    // Setters
    void setShipId(int id)
    {
        shipId = id;
    }

    void setCannonCount(int count)
    {
        cannon_count = count;
    }

    void setPirateCount(int count)
    {
        pirate_count = count;
    }

    // Getters
    int getShipId() const
    {
        return shipId;
    }

    int getCannonCount() const
    {
        return cannon_count;
    }

    int getPirateCount() const
    {
        return pirate_count;
    }

private:
    int shipId;
    int cannon_count;
    int pirate_count;
    shared_ptr<Ship> left_son, right_son;
    weak_ptr<Ship> father;
    weak_ptr<Pirate> first, last, money_root;
};

#endif // SHIPS_H
