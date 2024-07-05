#ifndef PIRATES_H
#define PIRATES_H

#include "pirates24b1.h"
#include "wet1util.h"
#include "ship.h"
#include <memory>

using namespace std;

class Ship;

class Pirate
{

public:
    Pirate() {}

    ~Pirate() {}

    void setPirateId(int id)
    {
        pirateId = id;
    }

    int getPirateId() const
    {
        return pirateId;
    }

    void setTreasure(int value)
    {
        treasure = value;
    }

    int getTreasure() const
    {
        return treasure;
    }

    void setMaxTreasure(int value)
    {
        max_treasure = value;
    }

    int getMaxTreasure() const
    {
        return max_treasure;
    }

private:
    int pirateId;
    int treasure;
    int max_treasure;
    shared_ptr<Pirate> left_son, right_son;
    weak_ptr<Pirate> father;
    weak_ptr<Pirate> prev, next;
    weak_ptr<Pirate> money_father, money_left_son, money_right_son;
    weak_ptr<Ship> ship;
};

#endif