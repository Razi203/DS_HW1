#include "pirates24b1.h"
#include <iostream>

Ocean::Ocean() : ship_root(nullptr), pirate_root(nullptr)
{
}

Ocean::~Ocean()
{
}

StatusType Ocean::add_ship(int shipId, int cannons)
{
    return StatusType::FAILURE;
}

StatusType Ocean::remove_ship(int shipId)
{
    return StatusType::FAILURE;
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure)
{
    return StatusType::FAILURE;
}

StatusType Ocean::remove_pirate(int pirateId)
{
    return StatusType::FAILURE;
}

StatusType Ocean::treason(int sourceShipId, int destShipId)
{
    if (sourceShipId <= ZERO || destShipId <= ZERO || sourceShipId == destShipId)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Ship> source_ship = findShip(sourceShipId);
    shared_ptr<Ship> dest_ship = findShip(destShipId);
    int pirate_count = source_ship->getPirateCount();

    if (source_ship == nullptr || dest_ship == nullptr || pirate_count == ZERO)
    {
        return StatusType::FAILURE;
    }

    shared_ptr<Pirate> first_pirate = source_ship->getFirstPirate();
    shared_ptr<Pirate> second_pirate = first_pirate->getNext();

    second_pirate->setPrev(nullptr);
    first_pirate->setNext(nullptr);
    first_pirate->setPrev(dest_ship->getLastPirate());
    first_pirate->getPrev()->setNext(first_pirate);
    first_pirate->setShip(dest_ship);

    dest_ship->setLastPirate(first_pirate);
    dest_ship->setFirstPirate(second_pirate);

    source_ship->setPirateCount(source_ship->getPirateCount() - ONE);
    dest_ship->setPirateCount(dest_ship->getPirateCount() + ONE);

    int source_trasure_modifier = source_ship->getTreasureModifier();
    int dest_trasure_modifier = dest_ship->getTreasureModifier();
    first_pirate->setTreasure(first_pirate->getTreasure() + source_trasure_modifier - dest_trasure_modifier);

    return StatusType::SUCCESS;
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change)
{
    if (pirateId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Pirate> pirate = findPirate(pirateId);

    if (pirate == nullptr)
    {
        return StatusType::FAILURE;
    }
    /**
     * remember to add remove and add of the pirate node after changing its treasure
     *
     *
     *
     *
     *
     *
     *
     */

    pirate->setTreasure(pirate->getTreasure() + change);
    return StatusType::SUCCESS;
}

output_t<int> Ocean::get_treasure(int pirateId)
{
    if (pirateId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    shared_ptr<Pirate> pirate = findPirate(pirateId);
    if (pirate == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    int modifier = pirate->getShip()->getTreasureModifier();
    return output_t<int>(pirate->getTreasure() + modifier);
}

output_t<int> Ocean::get_cannons(int shipId)
{
    if (shipId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    shared_ptr<Ship> ship = findShip(shipId);
    if (ship == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    return output_t<int>(ship->getCannonCount());
}

output_t<int> Ocean::get_richest_pirate(int shipId)
{
    return 0;
}

StatusType Ocean::ships_battle(int shipId1, int shipId2)
{
    return StatusType::FAILURE;
}

// orders
void Ocean::inorder(shared_ptr<Ship> node) const
{
    if (node == nullptr)
    {
        return;
    }
    inorder(node->getLeftSon());
    cout << *node;
    inorder(node->getRightSon());
}

void Ocean::inorder(shared_ptr<Pirate> node) const
{
    if (node == nullptr)
    {
        return;
    }
    inorder(node->getLeftSon());
    cout << *node;
    inorder(node->getRightSon());
}

void Ocean::preorder(shared_ptr<Ship> node) const
{
    if (node == nullptr)
    {
        return;
    }
    cout << *node;
    inorder(node->getLeftSon());
    inorder(node->getRightSon());
}
void Ocean::preorder(shared_ptr<Pirate> node) const
{
    if (node == nullptr)
    {
        return;
    }
    cout << *node;
    inorder(node->getLeftSon());
    inorder(node->getRightSon());
}

void Ocean::postorder(shared_ptr<Ship> node) const
{
    if (node == nullptr)
    {
        return;
    }
    inorder(node->getLeftSon());
    inorder(node->getRightSon());
    cout << *node;
}

void Ocean::postorder(shared_ptr<Pirate> node) const
{
    if (node == nullptr)
    {
        return;
    }
    inorder(node->getLeftSon());
    inorder(node->getRightSon());
    cout << *node;
}

shared_ptr<Ship> Ocean::findShip(int shipId)
{
    shared_ptr<Ship> current = ship_root;
    while (current)
    {
        int curId = current->getShipId();
        if (curId == shipId)
        {
            return current;
        }
        else if (shipId > curId)
        {

            current = current->getLeftSon();
        }
        else
        {

            current = current->getRightSon();
        }
    }

    return nullptr;
}

shared_ptr<Pirate> Ocean::findPirate(int pirateId)
{
    shared_ptr<Pirate> current = pirate_root;
    while (current)
    {
        int curId = current->getPirateId();
        if (curId == pirateId)
        {
            return current;
        }
        else if (pirateId > curId)
        {

            current = current->getLeftSon();
        }
        else
        {

            current = current->getRightSon();
        }
    }

    return nullptr;
}