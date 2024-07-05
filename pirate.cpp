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

shared_ptr<Pirate> Pirate::LL(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getParent();
    shared_ptr<Pirate> temp = getLeftSon();
    setLeftSon(nullptr);
    temp->setParent(parent);
    if (parent != nullptr)
    {
        if (parent->getLeftSon() == node_pointer)
        {
            parent->setLeftSon(temp);
        }
        else
        {
            parent->setRightSon(temp);
        }
    }
    setLeftSon(temp->getRightSon());
    temp->getRightSon()->setParent(node_pointer);
    temp->setRightSon(node_pointer);
    node_pointer->setParent(temp);
    updateHeight();
    temp->updateHeight();
    return temp;
}

shared_ptr<Pirate> Pirate::RR(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getParent();
    shared_ptr<Pirate> temp = getRightSon();
    setRightSon(nullptr);
    temp->setParent(parent);
    if (parent != nullptr)
    {
        if (parent->getLeftSon() == node_pointer)
        {
            parent->setLeftSon(temp);
        }
        else
        {
            parent->setRightSon(temp);
        }
    }
    setRightSon(temp->getLeftSon());
    temp->getLeftSon()->setParent(node_pointer);
    temp->setLeftSon(node_pointer);
    node_pointer->setParent(temp);
    updateHeight();
    temp->updateHeight();
    return temp;
}

shared_ptr<Pirate> Pirate::LR(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> left_son = getLeftSon();
    left_son->RR(left_son);
    left_son.reset();
    return LL(node_pointer);
}

shared_ptr<Pirate> Pirate::RL(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> right_son = getRightSon();
    right_son->LL(right_son);
    right_son.reset();
    return RR(node_pointer);
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

shared_ptr<Pirate> Pirate::LLMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getMoneyParent();
    shared_ptr<Pirate> temp = getMoneyLeftSon();
    setMoneyLeftSon(nullptr);
    temp->setMoneyParent(parent);
    if (parent != nullptr)
    {
        if (parent->getMoneyLeftSon() == node_pointer)
        {
            parent->setMoneyLeftSon(temp);
        }
        else
        {
            parent->setMoneyRightSon(temp);
        }
    }
    setMoneyLeftSon(temp->getMoneyRightSon());
    temp->setMoneyRightSon(node_pointer);
    temp->getMoneyRightSon()->setMoneyParent(node_pointer);
    node_pointer->setMoneyParent(temp);
    updateMoneyHeight();
    temp->updateMoneyHeight();
    return temp;
}

shared_ptr<Pirate> Pirate::RRMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> parent = getMoneyParent();
    shared_ptr<Pirate> temp = getMoneyRightSon();
    setMoneyRightSon(nullptr);
    temp->setMoneyParent(parent);
    if (parent->getMoneyLeftSon() == node_pointer)
    {
        parent->setMoneyLeftSon(temp);
    }
    else
    {
        parent->setMoneyRightSon(temp);
    }
    setMoneyRightSon(temp->getMoneyLeftSon());
    temp->setMoneyLeftSon(node_pointer);
    temp->getMoneyLeftSon()->setMoneyParent(node_pointer);
    node_pointer->setMoneyParent(temp);
    updateMoneyHeight();
    temp->updateMoneyHeight();
    return temp;
}

shared_ptr<Pirate> Pirate::LRMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> left_son = getMoneyLeftSon();
    left_son->RRMoney(left_son);
    left_son.reset();
    return LLMoney(node_pointer);
}

shared_ptr<Pirate> Pirate::RLMoney(shared_ptr<Pirate> node_pointer)
{
    shared_ptr<Pirate> right_son = getMoneyRightSon();
    right_son->LLMoney(right_son);
    right_son.reset();
    return RRMoney(node_pointer);
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