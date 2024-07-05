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
    return StatusType::FAILURE;
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change)
{
    return StatusType::FAILURE;
}

output_t<int> Ocean::get_treasure(int pirateId)
{
    if (pirateId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    shared_ptr<Pirate> pirate = find_pirate(pirateId);
    if (pirate == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    return output_t<int>(pirate->getTreasure());
}

output_t<int> Ocean::get_cannons(int shipId)
{
    if (shipId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    shared_ptr<Ship> ship = find_ship(shipId);
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

shared_ptr<Ship> Ocean::find_ship(int shipId)
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

shared_ptr<Pirate> Ocean::find_pirate(int pirateId)
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