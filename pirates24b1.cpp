#include "pirates24b1.h"
#include <iostream>

StatusType Ocean::add_ship(int shipId, int cannons)
{

    return StatusType::SUCCESS;
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
    if (sourceShipId <= ZERO || destShipId <= ZERO ||
        sourceShipId == destShipId)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Ship> source_ship = findShip(sourceShipId);
    shared_ptr<Ship> dest_ship = findShip(destShipId);

    if (source_ship == nullptr || dest_ship == nullptr ||
        !(source_ship->getPirateCount()))
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
    first_pirate->setTreasure(first_pirate->getTreasure() +
                              source_trasure_modifier - dest_trasure_modifier);

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

    shared_ptr<Ship> ship = pirate->getShip();
    ship->getMoneyPirates().remove(pirate);
    pirate->setTreasure(pirate->getTreasure() + change);
    ship->getMoneyPirates().insert(pirate);
    /**
     * remember to add remove and add of the pirate node after changing its treasure
     * same shit for treason
     *
     *
     *
     *
     *
     *
     *
     */

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
    if (shipId <= ZERO)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Ship> ship = findShip(shipId);

    if (ship == nullptr || !(ship->getPirateCount()))
    {
        return output_t<int>(StatusType::FAILURE);
    }

    int richest_pirate_id = ship->getMoneyPirates().root->max_Id.lock()->inner_node->getPirateId();
    return output_t<int>(richest_pirate_id);
}

StatusType Ocean::ships_battle(int shipId1, int shipId2)
{
    if (shipId1 <= ZERO || shipId2 <= ZERO || shipId1 == shipId2)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Ship> ship1 = findShip(shipId1);
    shared_ptr<Ship> ship2 = findShip(shipId2);

    if (ship1 == nullptr || ship2 == nullptr)
    {
        return StatusType::FAILURE;
    }

    int p1 = ship1->getPirateCount();
    int p2 = ship2->getPirateCount();
    int c1 = ship1->getCannonCount();
    int c2 = ship2->getCannonCount();

    int min_ship1 = (p1 >= c1) ? c1 : p1;
    int min_ship2 = (p2 >= c2) ? c2 : p2;

    if (min_ship1 > min_ship2)
    {
        ship1->setTreasureModifier(ship1->getTreasureModifier() + p2);
        ship2->setTreasureModifier(ship2->getTreasureModifier() - p1);
    }
    else if (min_ship2 > min_ship1)
    {
        ship1->setTreasureModifier(ship1->getTreasureModifier() - p2);
        ship2->setTreasureModifier(ship2->getTreasureModifier() + p1);
    }

    return StatusType::SUCCESS;
}

shared_ptr<AVLTreeNode<Ship>> Ocean::findShipLocation(int shipId)
{
    auto current = ships_tree.root;
    if (current == nullptr)
        return nullptr;
    auto previous = current;
    while (current)
    {
        int curId = current->inner_node->getShipId();
        previous = current;
        if (curId == shipId)
        {
            return current;
        }
        else if (shipId > curId)
        {
            current = current->left_son;
        }
        else
        {
            current = current->right_son;
        }
    }
    return previous;
}

shared_ptr<AVLTreeNode<Pirate>> Ocean::findPirateLocation(int pirateId)
{
    auto current = pirates_tree.root;
    if (current == nullptr)
        return nullptr;
    auto previous = current;
    while (current)
    {
        int curId = current->inner_node->getPirateId();
        previous = current;
        if (curId == pirateId)
        {
            return current;
        }
        else if (pirateId > curId)
        {

            current = current->left_son;
        }
        else
        {

            current = current->right_son;
        }
    }

    return previous;
}

shared_ptr<Ship> Ocean::findShip(int shipId)
{
    auto current = findShipLocation(shipId);
    if (current == nullptr || current->inner_node->getShipId() != shipId)
        return nullptr;
    return current->inner_node;
}

shared_ptr<Pirate> Ocean::findPirate(int pirateId)
{
    auto current = findPirateLocation(pirateId);
    if (current == nullptr || current->inner_node->getPirateId() != pirateId)
        return nullptr;
    return current->inner_node;
}