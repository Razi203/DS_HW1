#include "pirates24b1.h"
#include <iostream>

Ocean::Ocean()
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
    return 0;
}

output_t<int> Ocean::get_cannons(int shipId)
{
    return 0;
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
void Ocean::prerder(shared_ptr<Pirate> node) const
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
