#include "ship.h"
#include <iostream>

using namespace std;

void Ship::print(ostream &os) const
{
    os << "Ship ID: " << shipId << ", Cannon Amount: " << cannon_count << endl;
}

ostream &operator<<(ostream &os, const Ship &ship)
{
    ship.print(os);
    return os;
}

int Ship::getBF()
{
    int left_height = (getLeftSon() != nullptr) ? getLeftSon()->getHeight() : -1;
    int right_height = (getRightSon() != nullptr) ? getRightSon()->getHeight() : -1;
    return left_height - right_height;
}

void Ship::updateHeight()
{
    int left_height = (getLeftSon() != nullptr) ? getLeftSon()->getHeight() : -1;
    int right_height = (getRightSon() != nullptr) ? getRightSon()->getHeight() : -1;
    setHeight((left_height < right_height) ? right_height + 1 : left_height + 1);
}

void Ship::LL(shared_ptr<Ship> node_pointer)
{
    shared_ptr<Ship> parent = getParent();
    shared_ptr<Ship> temp(new Ship());
    temp->setLeftSon(getLeftSon());
    setLeftSon(nullptr);
    if (parent->getLeftSon() == node_pointer)
    {
        parent->setLeftSon(temp->getLeftSon());
    }
    else
    {
        parent->setRightSon(temp->getLeftSon());
    }
    setLeftSon(temp->getLeftSon()->getRightSon());
    temp->getLeftSon()->setRightSon(node_pointer);
    updateHeight();
    temp->getLeftSon()->updateHeight();
}

void Ship::RR(shared_ptr<Ship> node_pointer)
{
    shared_ptr<Ship> parent = getParent();
    shared_ptr<Ship> temp(new Ship());
    temp->setRightSon(getRightSon());
    setRightSon(nullptr);
    if (parent->getLeftSon() == node_pointer)
    {
        parent->setLeftSon(temp->getRightSon());
    }
    else
    {
        parent->setRightSon(temp->getRightSon());
    }
    setRightSon(temp->getRightSon()->getLeftSon());
    temp->getRightSon()->setLeftSon(node_pointer);
    updateHeight();
    temp->getRightSon()->updateHeight();
}

void Ship::LR(shared_ptr<Ship> node_pointer)
{
    shared_ptr<Ship> left_son = getLeftSon();
    left_son->RR(left_son);
    left_son.reset();
    LL(node_pointer);
}

void Ship::RL(shared_ptr<Ship> node_pointer)
{
    shared_ptr<Ship> right_son = getRightSon();
    right_son->LL(right_son);
    right_son.reset();
    RR(node_pointer);
}

// #######################################################################
// #######################################################################
// #######################################################################

// Setters
void Ship::setShipId(int id)
{
    shipId = id;
}

void Ship::setCannonCount(int count)
{
    cannon_count = count;
}

void Ship::setPirateCount(int count)
{
    pirate_count = count;
}

void Ship::setHeight(int h)
{
    height = h;
}

void Ship::setLeftSon(shared_ptr<Ship> son)
{
    left_son = son;
}
void Ship::setRightSon(shared_ptr<Ship> son)
{
    right_son = son;
}
void Ship::setParent(weak_ptr<Ship> parent)
{
    this->parent = parent;
}
void Ship::setFirstPirate(weak_ptr<Pirate> pirate)
{
    first_pirate = pirate;
}
void Ship::setLastPirate(weak_ptr<Pirate> pirate)
{
    last_pirate = pirate;
}
void Ship::setMoneyRoot(weak_ptr<Pirate> root)
{
    money_root = root;
}

// Getters
int Ship::getShipId() const
{
    return shipId;
}

int Ship::getCannonCount() const
{
    return cannon_count;
}

int Ship::getPirateCount() const
{
    return pirate_count;
}

int Ship::getHeight() const
{
    return height;
}

int Ship::getTreasureModifier() const
{
    return treasure_modifier;
}

shared_ptr<Ship> Ship::getLeftSon() const
{
    return left_son;
}
shared_ptr<Ship> Ship::getRightSon() const
{
    return right_son;
}
shared_ptr<Ship> Ship::getParent() const
{
    return parent.lock();
}
shared_ptr<Pirate> Ship::getFirstPirate() const
{
    return first_pirate.lock();
}
shared_ptr<Pirate> Ship::getLastPirate() const
{
    return last_pirate.lock();
}
shared_ptr<Pirate> Ship::getMoneyRoot() const
{
    return money_root.lock();
}