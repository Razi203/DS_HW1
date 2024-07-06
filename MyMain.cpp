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

    cout << "_____________________________" << endl;
    obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("first_ship_money1.dot");
    obj->pirates_tree.generateDotFile("pirates1.dot");
    print("update treasure", obj->update_pirate_treasure(2, 50));
    obj->pirates_tree.generateDotFile("pirates2.dot");
    obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("first_ship_money2.dot");

    cout << "_____________________________" << endl;
    print("get treasure", obj->get_treasure(2));
    print("get treasure", obj->get_treasure(4));
    print("get treasure", obj->get_treasure(42));
    print("get treasure", obj->get_treasure(32));
    cout << "_____________________________" << endl;

    print("get cannons", obj->get_cannons(1));
    print("get cannons", obj->get_cannons(2));
    print("get cannons", obj->get_cannons(-1));

    cout << "_____________________________" << endl;
    print("get richest pirate", obj->get_richest_pirate(1));
    print("remove pirate", obj->remove_pirate(2));
    print("get richest pirate", obj->get_richest_pirate(1));

    // obj->ships_tree.root->inner_node->getMoneyPirates().inOrder(obj->ships_tree.root->inner_node->getMoneyPirates().root);
    // obj->ships_tree.inOrder(obj->ships_tree.root);
    // cout << endl;
    // obj->ships_tree.postOrder(obj->ships_tree.root);
    // cout << endl;
    // obj->ships_tree.preOrder(obj->ships_tree.root);

    // std::cout << "DOT file generated: avltree1.dot" << std::endl;

    // print("remove", obj->remove_pirate(2));
    // print("remove", obj->remove_pirate(3));
    // obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("avltree2.dot");
    // std::cout << "DOT file generated: avltree2.dot" << std::endl;
    // obj->pirates_tree.generateDotFile("avltree3.dot");
    // std::cout << "DOT file generated: avltree3.dot" << std::endl;

    /**
     *
     *
     *
     */
    // Quit
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
