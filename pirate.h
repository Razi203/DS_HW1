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
    Pirate() : pirateId(ZERO), treasure(ZERO), left_son(nullptr), right_son(nullptr), parent(weak_ptr<Pirate>()), prev(weak_ptr<Pirate>()), next(weak_ptr<Pirate>()), money_parent(weak_ptr<Pirate>()), money_left_son(weak_ptr<Pirate>()), money_right_son(weak_ptr<Pirate>()), ship(weak_ptr<Ship>()) {}
    Pirate(int id, int value) : pirateId(id), treasure(value), left_son(nullptr), right_son(nullptr), parent(weak_ptr<Pirate>()), prev(weak_ptr<Pirate>()), next(weak_ptr<Pirate>()), money_parent(weak_ptr<Pirate>()), money_left_son(weak_ptr<Pirate>()), money_right_son(weak_ptr<Pirate>()), ship(weak_ptr<Ship>()) {}

    ~Pirate() {}

    void print(ostream &os) const;

    friend ostream &operator<<(ostream &os, const Pirate &pirate);

    shared_ptr<Pirate> LL(shared_ptr<Pirate> node_pointer);
    shared_ptr<Pirate> RR(shared_ptr<Pirate> node_pointer);
    shared_ptr<Pirate> RL(shared_ptr<Pirate> node_pointer);
    shared_ptr<Pirate> LR(shared_ptr<Pirate> node_pointer);

    shared_ptr<Pirate> LLMoney(shared_ptr<Pirate> node_pointer);
    shared_ptr<Pirate> RRMoney(shared_ptr<Pirate> node_pointer);
    shared_ptr<Pirate> RLMoney(shared_ptr<Pirate> node_pointer);
    shared_ptr<Pirate> LRMoney(shared_ptr<Pirate> node_pointer);

    void updateHeight();
    void updateMoneyHeight();

    int getBF();
    int getMoneyBF();

    // Setters

    void setPirateId(int id);
    void setTreasure(int value);
    void setMaxTreasure(int value);
    void setPrev(shared_ptr<Pirate> p);
    void setNext(shared_ptr<Pirate> n);

    void setHeightChoose(int h, int mode);
    void setParentChoose(shared_ptr<Pirate> f, int mode);
    void setLeftSonChoose(shared_ptr<Pirate> son, int mode);
    void setRightSonChoose(shared_ptr<Pirate> son, int mode);

    void setHeight(int h);
    void setParent(shared_ptr<Pirate> f);
    void setLeftSon(shared_ptr<Pirate> son);
    void setRightSon(shared_ptr<Pirate> son);

    void setMoneyHeight(int mh);
    void setMoneyParent(shared_ptr<Pirate> mf);
    void setMoneyLeftSon(shared_ptr<Pirate> ml);
    void setMoneyRightSon(shared_ptr<Pirate> mr);

    void setShip(shared_ptr<Ship> s);

    // Getters
    int getPirateId() const;
    int getMaxTreasure() const;
    int getTreasure() const;
    int getHeight() const;
    int getMoneyHeight() const;
    shared_ptr<Pirate> getLeftSon() const;
    shared_ptr<Pirate> getRightSon() const;
    shared_ptr<Pirate> getParent() const;
    shared_ptr<Pirate> getPrev() const;
    shared_ptr<Pirate> getNext() const;
    shared_ptr<Pirate> getMoneyParent() const;
    shared_ptr<Pirate> getMoneyLeftSon() const;
    shared_ptr<Pirate> getMoneyRightSon() const;
    shared_ptr<Ship> getShip() const;

private:
    int pirateId;
    int treasure;
    int max_treasure;
    int height, money_height;
    shared_ptr<Pirate> left_son, right_son;
    weak_ptr<Pirate> parent;
    weak_ptr<Pirate> prev, next;
    weak_ptr<Pirate> money_parent, money_left_son, money_right_son;
    weak_ptr<Ship> ship;
};

class PirateCompare // true if b > a
{
    bool operator()(shared_ptr<Pirate> a, shared_ptr<Pirate> b) const
    {
        return a->getPirateId() < b->getPirateId();
    }
};

class MoneyCompare // true if b > a
{
    bool operator()(shared_ptr<Pirate> a, shared_ptr<Pirate> b) const
    {
        if (a->getTreasure() < b->getTreasure())
            return true;
        else if (a->getTreasure() > b->getTreasure())
            return false;
        else if (a->getPirateId() < b->getPirateId())
            return true;
        else
            return false;
    }
};

#endif