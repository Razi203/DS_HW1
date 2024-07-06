#include "pirates24b1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);

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
    print("get richest pirate", obj->get_richest_pirate(1));

    cout << "_____________________________" << endl;

    print("add ship", obj->add_ship(2, 30));
    print("add pirate", obj->add_pirate(31, 12, 20));
    print("add pirate", obj->add_pirate(42, 2, 30));
    print("add pirate", obj->add_pirate(54, 2, 30));
    print("add pirate", obj->add_pirate(59, 2, 10));
    print("get richest pirate", obj->get_richest_pirate(2));
    obj->ships_tree.generateDotFile("ships1.dot");

    cout << "_____________________________" << endl;
    obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("first_ship_money1.dot");
    obj->pirates_tree.generateDotFile("pirates1.dot");
    print("update treasure", obj->update_pirate_treasure(2, 20));
    obj->pirates_tree.generateDotFile("pirates2.dot");
    obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("first_ship_money2.dot");
    cout << "_____________________________" << endl;
    // print("remove pirate", obj->remove_pirate(2));
    print("treason", obj->treason(1, 2));
    print("treason", obj->treason(1, 2));
    print("treason", obj->treason(1, 2));
    print("treason", obj->treason(1, 2));
    print("treason", obj->treason(1, 2));
    print("treason", obj->treason(2, 2));
    print("treason", obj->treason(2, 1));
    print("treason", obj->treason(2, 1));
    print("treason", obj->treason(2, 1));

    print("get richest pirate", obj->get_richest_pirate(1));
    print("get richest pirate", obj->get_richest_pirate(2));
    // print("remove pirate", obj->remove_pirate(5));
    // print("remove pirate", obj->remove_pirate(4));
    cout << (obj->ships_tree.root->inner_node->getMoneyPirates().root != nullptr) + 5 << endl;
    // print("treason", obj->treason(1, 2));
    // print("remove pirate", obj->remove_pirate(5));
    // print("remove pirate", obj->remove_pirate(4));
    // print("remove ship", obj->remove_ship(1));
    obj->ships_tree.generateDotFile("ships2.dot");
    obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("first_ship_money3.dot");
    obj->ships_tree.root->right_son->inner_node->getMoneyPirates().generateDotFile("second_ship_money3.dot");
    obj->pirates_tree.generateDotFile("pirates3.dot");
    // print("get richest pirate", obj->get_richest_pirate(1));
    // print("get richest pirate", obj->get_richest_pirate(2));
    // cout << "_____________________________" << endl;
    // print("remove ship", obj->remove_ship(1));
    // print("remove ship", obj->remove_ship(1));
    // print("remove ship", obj->remove_ship(1));
    // cout << *(obj->ships_tree.root->inner_node) << endl;

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
