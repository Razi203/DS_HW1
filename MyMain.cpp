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
    print("add_ship(1, 10)", obj->add_ship(1, 10));
    print("add_ship(2, 20)", obj->add_ship(2, 20));
    print("add_ship(3, 30)", obj->add_ship(3, 30));
    print("add_ship(4, 40)", obj->add_ship(4, 40));
    print("add_ship(5, 50)", obj->add_ship(5, 50));
    print("add_ship(6, 60)", obj->add_ship(6, 60));
    print("add_ship(7, 70)", obj->add_ship(7, 70));
    print("add_ship(8, 80)", obj->add_ship(8, 80));
    obj->ships_tree.inOrder(obj->ships_tree.root);
    cout << endl;
    obj->ships_tree.postOrder(obj->ships_tree.root);
    cout << endl;
    obj->ships_tree.preOrder(obj->ships_tree.root);

    obj->ships_tree.generateDotFile("avltree1.dot");
    std::cout << "DOT file generated: avltree1.dot" << std::endl;

    print("remove", obj->remove_ship(1));
    obj->ships_tree.generateDotFile("avltree2.dot");
    std::cout << "DOT file generated: avltree2.dot" << std::endl;
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
