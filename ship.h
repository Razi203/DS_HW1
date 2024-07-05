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
    Ship() : shipId(ZERO), cannon_count(ZERO),
             pirate_count(ZERO), left_son(nullptr), right_son(nullptr), parent(),
             first_pirate(), last_pirate(), money_root()
    {
    }

    Ship(int id, int cannons) : shipId(id), cannon_count(cannons),
                                pirate_count(ZERO), treasure_modifier(ZERO), left_son(nullptr), right_son(nullptr), parent(),
                                first_pirate(), last_pirate(), money_root()
    {
    }

    ~Ship()
    {
    }

    void print(ostream &os) const;

    friend ostream &operator<<(ostream &os, const Ship &ship);

    shared_ptr<Ship> LL(shared_ptr<Ship> node_pointer);
    shared_ptr<Ship> RR(shared_ptr<Ship> node_pointer);
    shared_ptr<Ship> RL(shared_ptr<Ship> node_pointer);
    shared_ptr<Ship> LR(shared_ptr<Ship> node_pointer);

    void updateHeight();

    int getBF();

    // Setters
    void setShipId(int id);
    void setCannonCount(int count);
    void setPirateCount(int count);
    void setHeight(int h);
    void setLeftSon(shared_ptr<Ship> son);
    void setRightSon(shared_ptr<Ship> son);
    void setParent(weak_ptr<Ship> parent);
    void setFirstPirate(weak_ptr<Pirate> pirate);
    void setLastPirate(weak_ptr<Pirate> pirate);
    void setMoneyRoot(weak_ptr<Pirate> root);
    void setTreasureModifier(int change);

    // Getters
    int getShipId() const;
    int getCannonCount() const;
    int getPirateCount() const;
    int getHeight() const;
    int getTreasureModifier() const;
    shared_ptr<Ship> getLeftSon() const;
    shared_ptr<Ship> getRightSon() const;
    shared_ptr<Ship> getParent() const;
    shared_ptr<Pirate> getFirstPirate() const;
    shared_ptr<Pirate> getLastPirate() const;
    shared_ptr<Pirate> getMoneyRoot() const;

private:
    int shipId;
    int cannon_count;
    int pirate_count;
    int height;
    int treasure_modifier;
    weak_ptr<Pirate> first_pirate, last_pirate;
    AVLTree<Pirate, MoneyCompare> moeny_pirates;
};

class ShipCompare
{
    bool operator()(shared_ptr<Ship> a, shared_ptr<Ship> b) const
    {
        return a->getShipId() < b->getShipId();
    }
};
#endif // SHIPS_H
