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
    Pirate(int id, int value) : pirateId(id), treasure(value), left_son(nullptr), right_son(nullptr), father(weak_ptr<Pirate>()), prev(weak_ptr<Pirate>()), next(weak_ptr<Pirate>()), money_father(weak_ptr<Pirate>()), money_left_son(weak_ptr<Pirate>()), money_right_son(weak_ptr<Pirate>()), ship(weak_ptr<Ship>()) {}

    ~Pirate() {}

    void print(ostream &os) const;

    friend ostream &operator<<(ostream &os, const Pirate &pirate);

    // Setters
    void setPirateId(int id)
    {
        pirateId = id;
    }

    void setTreasure(int value)
    {
        treasure = value;
    }

    void setMaxTreasure(int value)
    {
        max_treasure = value;
    }

    void setLeftSon(shared_ptr<Pirate> son)
    {
        left_son = son;
    }
    void setRightSon(shared_ptr<Pirate> son)
    {
        right_son = son;
    }
    void setFather(weak_ptr<Pirate> f)
    {
        father = f;
    }
    void setPrev(weak_ptr<Pirate> p)
    {
        prev = p;
    }
    void setNext(weak_ptr<Pirate> n)
    {
        next = n;
    }
    void setMoneyFather(weak_ptr<Pirate> mf)
    {
        money_father = mf;
    }
    void setMoneyLeftSon(weak_ptr<Pirate> ml)
    {
        money_left_son = ml;
    }
    void setMoneyRightSon(weak_ptr<Pirate> mr)
    {
        money_right_son = mr;
    }
    void setShip(weak_ptr<Ship> s)
    {
        ship = s;
    }

    // Getters

    int getPirateId() const
    {
        return pirateId;
    }
    int getMaxTreasure() const
    {
        return max_treasure;
    }

    int getTreasure() const
    {
        return treasure;
    }

    shared_ptr<Pirate> getLeftSon() const
    {
        return left_son;
    }
    shared_ptr<Pirate> getRightSon() const
    {
        return right_son;
    }
    weak_ptr<Pirate> getFather() const
    {
        return father;
    }
    weak_ptr<Pirate> getPrev() const
    {
        return prev;
    }
    weak_ptr<Pirate> getNext() const
    {
        return next;
    }
    weak_ptr<Pirate> getMoneyFather() const
    {
        return money_father;
    }
    weak_ptr<Pirate> getMoneyLeftSon() const
    {
        return money_left_son;
    }
    weak_ptr<Pirate> getMoneyRightSon() const
    {
        return money_right_son;
    }
    weak_ptr<Ship> getShip() const
    {
        return ship;
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