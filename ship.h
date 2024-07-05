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
                                first_pirate(), last_pirate(), money_root()
    {
    }

    ~Ship()
    {
    }

    void print(ostream &os) const;

    friend ostream &operator<<(ostream &os, const Ship &ship);

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
    void setLeftSon(shared_ptr<Ship> son)
    {
        left_son = son;
    }
    void setRightSon(shared_ptr<Ship> son)
    {
        right_son = son;
    }
    void setFather(weak_ptr<Ship> father)
    {
        this->father = father;
    }
    void setFirstPirate(weak_ptr<Pirate> pirate)
    {
        first_pirate = pirate;
    }
    void setLastPirate(weak_ptr<Pirate> pirate)
    {
        last_pirate = pirate;
    }
    void setMoneyRoot(weak_ptr<Pirate> root)
    {
        money_root = root;
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
    shared_ptr<Ship> getLeftSon() const
    {
        return left_son;
    }
    shared_ptr<Ship> getRightSon() const
    {
        return right_son;
    }
    weak_ptr<Ship> getFather() const
    {
        return father;
    }
    weak_ptr<Pirate> getFirstPirate() const
    {
        return first_pirate;
    }
    weak_ptr<Pirate> getLastPirate() const
    {
        return last_pirate;
    }
    weak_ptr<Pirate> getMoneyRoot() const
    {
        return money_root;
    }

private:
    int shipId;
    int cannon_count;
    int pirate_count;
    shared_ptr<Ship> left_son, right_son;
    weak_ptr<Ship> father;
    weak_ptr<Pirate> first_pirate, last_pirate, money_root;
};

#endif // SHIPS_H
