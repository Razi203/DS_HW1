#include "pirates24b1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void print(Ocean *obj, int index);
void print(Ocean *obj, int index, int ship);
void lineBreak();

int main()
{

    // Init
    Ocean *obj = new Ocean();
    print("Ocean()", StatusType::SUCCESS);
    print("add ship", obj->add_ship(1, 10));
    print("add pirate", obj->add_pirate(1, 1, 50));
    print("add pirate", obj->add_pirate(2, 1, 20));
    print("add pirate", obj->add_pirate(4, 1, 30));
    print("add pirate", obj->add_pirate(4, 1, 30));
    print("add pirate", obj->add_pirate(5, 1, 10));

    lineBreak();

    print("add ship", obj->add_ship(2, 30));
    print("add pirate", obj->add_pirate(31, 12, 20));
    print("add pirate", obj->add_pirate(42, 2, 30));
    print("add pirate", obj->add_pirate(54, 2, 30));
    print("add pirate", obj->add_pirate(59, 2, 10));

    print(obj, 1, 1);
    print(obj, 1);

    lineBreak();

    print("remove pirate2", obj->remove_pirate(2));
    print(obj, 2, 1);
    print(obj, 2);

    lineBreak();

    print("remove pirate6", obj->remove_pirate(6));
    print(obj, 3, 1);
    print(obj, 3);

    lineBreak();

    print("remove pirate5", obj->remove_pirate(5));
    print(obj, 4);
    print(obj, 4, 1);
    print(obj, 4, 2);

    lineBreak();

    print("treason1", obj->treason(2, 1));
    print(obj, 5);
    print(obj, 5, 1);
    print(obj, 5, 2);

    lineBreak();

    print("treason2", obj->treason(2, 1));
    print(obj, 6);
    print(obj, 6, 1);
    print(obj, 6, 2);

    lineBreak();

    print("add ship", obj->add_ship(3, 5));
    print("get richest1", obj->get_richest_pirate(3));

    lineBreak();

    print("battle1", obj->ships_battle(1, 2));
    print("battle1", obj->get_treasure(6));
    print("battle1", obj->get_treasure(42));
    print("battle1", obj->get_treasure(59));

    lineBreak();

    print("add ship", obj->remove_ship(3));

    lineBreak();

    print("treason2", obj->treason(2, 1));
    print(obj, 7);
    print(obj, 7, 1);
    print(obj, 7, 2);

    lineBreak();

    print("battle1", obj->ships_battle(1, 3));

    print("remove ship", obj->remove_ship(2));
    print("remove ship", obj->remove_ship(1));

    print("remove pirate", obj->remove_pirate(59));
    print("remove pirate", obj->remove_pirate(54));
    print("remove pirate", obj->remove_pirate(1));
    print("remove pirate", obj->remove_pirate(4));
    print("remove pirate", obj->remove_pirate(42));
    print("remove ship", obj->remove_ship(1));
    print(obj, 8);

    lineBreak();

    print("add ship", obj->add_ship(2, 3));
    print("add ship", obj->add_ship(1, 2));

    print("add pirate", obj->add_pirate(1, 2, 50));
    print("add pirate", obj->add_pirate(2, 1, 20));
    print("add pirate", obj->add_pirate(4, 2, 30));
    print("add pirate", obj->add_pirate(4, 1, 30));
    print("add pirate", obj->add_pirate(5, 2, 10));

    print(obj, 9);
    print(obj, 9, 1);
    print(obj, 9, 2);

    lineBreak();

    print("update pirate treasure", obj->update_pirate_treasure(5, -20));
    print(obj, 10);

    lineBreak();
    print("battle1", obj->ships_battle(1, 2));
    print(obj, 11);
    print(obj, 11, 1);
    print(obj, 11, 2);

    lineBreak();
    print("remove pirate2", obj->remove_pirate(2));

    for (int i = 0; i <= 100; i++)
    {
        print("add pirate", obj->add_pirate(i, 1, i + 1));
    }
    print(obj, 12);

    lineBreak();

    for (int i = 50; i <= 150; i++)
    {
        print("remove pirate", obj->remove_pirate(i));
    }
    print(obj, 13);

    lineBreak();

    for (int i = 0; i <= 100; i++)
    {
        print("treason100", obj->treason(2, 1));
    }
    print(obj, 14);
    print(obj, 14, 1);
    print(obj, 14, 2);

    lineBreak();

    for (int i = 0; i <= 100; i++)
    {
        print("treason100", obj->treason(1, 2));
    }
    print(obj, 15);
    print(obj, 15, 1);
    print(obj, 15, 2);

    lineBreak();
    print("treason55", obj->treason(1, 2));

    lineBreak();

    for (int i = 0; i <= 10; i++)
    {
        print("treason100", obj->treason(2, 1));
    }
    print(obj, 16);
    print(obj, 16, 1);
    print(obj, 16, 2);

    lineBreak();

    print("battle", obj->ships_battle(1, 2));
    print(obj, 17);
    print(obj, 17, 1);
    print(obj, 17, 2);

    lineBreak();

    delete obj;
    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
    {
        "SUCCESS",
        "ALLOCATION_ERROR",
        "INVALID_INPUT",
        "FAILURE"};

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int)res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS)
    {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << ", " << res.ans() << endl;
    }
    else
    {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << endl;
    }
}

void print(Ocean *obj, int index)
{
    obj->ships_tree.generateDotFile("ships" + to_string(index) + ".dot");
    obj->pirates_tree.generateDotFile("pirates" + to_string(index) + ".dot");
}

void print(Ocean *obj, int index, int ship)
{
    auto ship_pointer = obj->findShip(ship);
    if (ship_pointer != nullptr)
    {
        ship_pointer->getMoneyPirates().generateDotFile("ship_" + to_string(ship) + "_pirates" + to_string(index) + ".dot");
    }
    else
    {
        cout << "SHIP " << ship << " NOT FOUND!!!" << endl;
    }
}

void lineBreak()
{
    cout << "_____________________________" << endl;
}