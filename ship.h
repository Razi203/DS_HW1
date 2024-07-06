#ifndef SHIPS_H
#define SHIPS_H

#include <memory>
#include "pirates24b1.h"
#include "AVLTree.h"
#include "wet1util.h"
#include "ship.h"

using namespace std;

class Pirate;

class Ship
{
public:
    Ship::Ship(int id, int cannons) : shipId(id), cannon_count(cannons),
                                      pirate_count(ZERO), treasure_modifier(ZERO),
                                      first_pirate(), last_pirate() {}
    ~Ship() {}

    void print(ostream &os) const;
    friend ostream &operator<<(ostream &os, const Ship &ship);

    // Setters
    void setShipId(int id);
    void setCannonCount(int count);
    void setPirateCount(int count);
    void setHeight(int h);
    void setFirstPirate(shared_ptr<Pirate> pirate);
    void setLastPirate(shared_ptr<Pirate> pirate);
    void setTreasureModifier(int change);

    // Getters
    int getShipId() const;
    int getCannonCount() const;
    int getPirateCount() const;
    int getHeight() const;
    int getTreasureModifier() const;
    AVLTree<Pirate, MoneyCompare> &getMoneyPirates();
    shared_ptr<Pirate> getFirstPirate() const;
    shared_ptr<Pirate> getLastPirate() const;

private:
    int shipId;
    int cannon_count;
    int pirate_count;
    int height;
    int treasure_modifier;
    weak_ptr<Pirate> first_pirate, last_pirate;
    AVLTree<Pirate, MoneyCompare> money_pirates;
};

class ShipCompare
{
    bool operator()(shared_ptr<Ship> a, shared_ptr<Ship> b) const
    {
        return a->getShipId() < b->getShipId();
    }
};
#endif // SHIPS_H
