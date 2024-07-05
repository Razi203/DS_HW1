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

int Pirate::getBF()
{
    int left_height = (getLeftSon() != nullptr) ? getLeftSon()->getHeight() : -1;
    int right_height = (getRightSon() != nullptr) ? getRightSon()->getHeight() : -1;
    return left_height - right_height;
}

void Pirate::updateHeight()
{
    int left_height = (getLeftSon() != nullptr) ? getLeftSon()->getHeight() : -1;
    int right_height = (getRightSon() != nullptr) ? getRightSon()->getHeight() : -1;
    setHeight((left_height < right_height) ? right_height + 1 : left_height + 1);
}

void Pirate::LL(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getParent();
    shared_ptr<Pirate> temp(new Pirate());
    temp->setLeftSon(getLeftSon());
    setLeftSon(nullptr);
    if (parent != nullptr)
    {
        if (parent->getLeftSon() == node_pointer)
        {
            parent->setLeftSon(temp->getLeftSon());
        }
        else
        {
            parent->setRightSon(temp->getLeftSon());
        }
    }
    setLeftSon(temp->getLeftSon()->getRightSon());
    temp->getLeftSon()->setRightSon(node_pointer);
    updateHeight();
    temp->getLeftSon()->updateHeight();
}

void Pirate::RR(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getParent();
    shared_ptr<Pirate> temp(new Pirate());
    temp->setRightSon(getRightSon());
    setRightSon(nullptr);
    if (parent != nullptr)
    {
        if (parent->getLeftSon() == node_pointer)
        {
            parent->setLeftSon(temp->getRightSon());
        }
        else
        {
            parent->setRightSon(temp->getRightSon());
        }
    }
    setRightSon(temp->getRightSon()->getLeftSon());
    temp->getRightSon()->setLeftSon(node_pointer);
    updateHeight();
    temp->getRightSon()->updateHeight();
}

void Pirate::LR(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> left_son = getLeftSon();
    left_son->RR(left_son);
    left_son.reset();
    LL(node_pointer);
}

void Pirate::RL(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> right_son = getRightSon();
    right_son->LL(right_son);
    right_son.reset();
    RR(node_pointer);
}

/**
 * Methods That Modify The Money sub Tree
 */

int Pirate::getMoneyBF()
{
    shared_ptr<Pirate> left_son = getMoneyLeftSon();
    shared_ptr<Pirate> right_son = getMoneyRightSon();
    int left_height = (left_son != nullptr) ? left_son->getHeight() : -1;
    int right_height = (right_son != nullptr) ? right_son->getHeight() : -1;
    return left_height - right_height;
}

void Pirate::updateMoneyHeight()
{
    shared_ptr<Pirate> left_son = getMoneyLeftSon();
    shared_ptr<Pirate> right_son = getMoneyRightSon();
    int left_height = (left_son != nullptr) ? left_son->getHeight() : -1;
    int right_height = (right_son != nullptr) ? right_son->getHeight() : -1;
    setMoneyHeight((left_height < right_height) ? right_height + 1 : left_height + 1);
}

void Pirate::LLMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getMoneyParent();
    shared_ptr<Pirate> temp(new Pirate());
    temp->setMoneyLeftSon(getMoneyLeftSon());
    setMoneyLeftSon(nullptr);
    if (parent != nullptr)
    {
        if (parent->getMoneyLeftSon() == node_pointer)
        {
            parent->setMoneyLeftSon(temp->getMoneyLeftSon());
        }
        else
        {
            parent->setMoneyRightSon(temp->getMoneyLeftSon());
        }
    }
    setLeftSon(temp->getMoneyLeftSon()->getMoneyRightSon());
    temp->getMoneyLeftSon()->setMoneyRightSon(node_pointer);
    updateMoneyHeight();
    temp->getMoneyLeftSon()->updateMoneyHeight();
}

void Pirate::RRMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getMoneyParent();
    shared_ptr<Pirate> temp(new Pirate());
    temp->setMoneyRightSon(getMoneyRightSon());
    setMoneyRightSon(nullptr);
    if (parent->getMoneyLeftSon() == node_pointer)
    {
        parent->setMoneyLeftSon(temp->getMoneyRightSon());
    }
    else
    {
        parent->setMoneyRightSon(temp->getMoneyRightSon());
    }
    setMoneyRightSon(temp->getMoneyRightSon()->getMoneyLeftSon());
    temp->getMoneyRightSon()->setMoneyLeftSon(node_pointer);
    updateMoneyHeight();
    temp->getMoneyRightSon()->updateMoneyHeight();
}

void Pirate::LRMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> left_son = getMoneyLeftSon();
    left_son->RRMoney(left_son);
    left_son.reset();
    LLMoney(node_pointer);
}

void Pirate::RLMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> right_son = getMoneyRightSon();
    right_son->LLMoney(right_son);
    right_son.reset();
    RRMoney(node_pointer);
}

// #######################################################################
// #######################################################################
// #######################################################################

// Setters
void Pirate::setPirateId(int id)
{
    pirateId = id;
}

void Pirate::setTreasure(int value)
{
    treasure = value;
}

void Pirate::setMaxTreasure(int value)
{
    max_treasure = value;
}

void Pirate::setHeight(int h)
{
    height = h;
}

void Pirate::setMoneyHeight(int mh)
{
    money_height = mh;
}

void Pirate::setLeftSon(shared_ptr<Pirate> son)
{
    left_son = son;
}
void Pirate::setRightSon(shared_ptr<Pirate> son)
{
    right_son = son;
}
void Pirate::setParent(shared_ptr<Pirate> f)
{
    parent = f;
}
void Pirate::setPrev(shared_ptr<Pirate> p)
{
    prev = p;
}
void Pirate::setNext(shared_ptr<Pirate> n)
{
    next = n;
}
void Pirate::setMoneyParent(shared_ptr<Pirate> mf)
{
    money_parent = mf;
}
void Pirate::setMoneyLeftSon(shared_ptr<Pirate> ml)
{
    money_left_son = ml;
}
void Pirate::setMoneyRightSon(shared_ptr<Pirate> mr)
{
    money_right_son = mr;
}
void Pirate::setShip(shared_ptr<Ship> s)
{
    ship = s;
}

// Getters

int Pirate::getPirateId() const
{
    return pirateId;
}
int Pirate::getMaxTreasure() const
{
    return max_treasure;
}

int Pirate::getTreasure() const
{
    return treasure;
}

int Pirate::getHeight() const
{
    return height;
}

int Pirate::getMoneyHeight() const
{
    return money_height;
}

int Pirate::getMaxId() const
{
    return max_id;
}

shared_ptr<Pirate> Pirate::getLeftSon() const
{
    return left_son;
}
shared_ptr<Pirate> Pirate::getRightSon() const
{
    return right_son;
}
shared_ptr<Pirate> Pirate::getParent() const
{
    return parent.lock();
}
shared_ptr<Pirate> Pirate::getPrev() const
{
    return prev.lock();
}
shared_ptr<Pirate> Pirate::getNext() const
{
    return next.lock();
}
shared_ptr<Pirate> Pirate::getMoneyParent() const
{
    return money_parent.lock();
}
shared_ptr<Pirate> Pirate::getMoneyLeftSon() const
{
    return money_left_son.lock();
}
shared_ptr<Pirate> Pirate::getMoneyRightSon() const
{
    return money_right_son.lock();
}
shared_ptr<Ship> Pirate::getShip() const
{
    return ship.lock();
}