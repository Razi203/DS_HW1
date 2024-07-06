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

    obj->ships_tree.root->inner_node->getMoneyPirates().inOrder(obj->ships_tree.root->inner_node->getMoneyPirates().root);
    // obj->ships_tree.inOrder(obj->ships_tree.root);
    // cout << endl;
    // obj->ships_tree.postOrder(obj->ships_tree.root);
    // cout << endl;
    // obj->ships_tree.preOrder(obj->ships_tree.root);

    obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("avltree1.dot");
    std::cout << "DOT file generated: avltree1.dot" << std::endl;

    print("remove", obj->remove_pirate(2));
    print("remove", obj->remove_pirate(3));
    obj->ships_tree.root->inner_node->getMoneyPirates().generateDotFile("avltree2.dot");
    std::cout << "DOT file generated: avltree2.dot" << std::endl;
    obj->pirates_tree.generateDotFile("avltree3.dot");
    std::cout << "DOT file generated: avltree3.dot" << std::endl;
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
