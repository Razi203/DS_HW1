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
    Pirate() : pirateId(ZERO), treasure(ZERO), left_son(nullptr), right_son(nullptr), father(weak_ptr<Pirate>()), prev(weak_ptr<Pirate>()), next(weak_ptr<Pirate>()), money_father(weak_ptr<Pirate>()), money_left_son(weak_ptr<Pirate>()), money_right_son(weak_ptr<Pirate>()), ship(weak_ptr<Ship>()) {}
    Pirate(int id, int value) : pirateId(id), treasure(value), left_son(nullptr), right_son(nullptr), father(weak_ptr<Pirate>()), prev(weak_ptr<Pirate>()), next(weak_ptr<Pirate>()), money_father(weak_ptr<Pirate>()), money_left_son(weak_ptr<Pirate>()), money_right_son(weak_ptr<Pirate>()), ship(weak_ptr<Ship>()) {}

    ~Pirate() {}

    void print(ostream &os) const;

    friend ostream &operator<<(ostream &os, const Pirate &pirate);

    void LL(shared_ptr<Pirate> node_pointer);
    void RR(shared_ptr<Pirate> node_pointer);
    void RL(shared_ptr<Pirate> node_pointer);
    void LR(shared_ptr<Pirate> node_pointer);

    void LLMoney(shared_ptr<Pirate> node_pointer);
    void RRMoney(shared_ptr<Pirate> node_pointer);
    void RLMoney(shared_ptr<Pirate> node_pointer);
    void LRMoney(shared_ptr<Pirate> node_pointer);

    void updateHeight();
    void updateMoneyHeight();

    int getBF();
    int getMoneyBF();

    // Setters
    void setPirateId(int id);
    void setTreasure(int value);
    void setMaxTreasure(int value);
    void setHeight(int h);
    void setMoneyHeight(int mh);
    void setLeftSon(shared_ptr<Pirate> son);
    void setRightSon(shared_ptr<Pirate> son);
    void setFather(shared_ptr<Pirate> f);
    void setPrev(shared_ptr<Pirate> p);
    void setNext(shared_ptr<Pirate> n);
    void setMoneyFather(shared_ptr<Pirate> mf);
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
    shared_ptr<Pirate> getFather() const;
    shared_ptr<Pirate> getPrev() const;
    shared_ptr<Pirate> getNext() const;
    shared_ptr<Pirate> getMoneyFather() const;
    shared_ptr<Pirate> getMoneyLeftSon() const;
    shared_ptr<Pirate> getMoneyRightSon() const;
    shared_ptr<Ship> getShip() const;

private:
    int pirateId;
    int treasure;
    int max_treasure;
    int height, money_height;
    shared_ptr<Pirate> left_son, right_son;
    weak_ptr<Pirate> father;
    weak_ptr<Pirate> prev, next;
    weak_ptr<Pirate> money_father, money_left_son, money_right_son;
    weak_ptr<Ship> ship;
};

#endif