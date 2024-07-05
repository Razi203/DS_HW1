#include <memory>
#include "pirates24b1.h"

using namespace std;

const int static POSITIVE_UNBALANCED = 2;
const int static NEGATIVE_UNBALANCED = -2;

template <typename T>
class AVLTreeNode
{
public:
    shared_ptr<T> inner_node;
    shared_ptr<AVLTreeNode<T>> left_son;
    shared_ptr<AVLTreeNode<T>> right_son;
    shared_ptr<AVLTreeNode<T>> parent;
    int height;

    AVLTreeNode(const shared_ptr<T> &node)
        : inner_node(node), left_son(nullptr), right_son(nullptr), parent(nullptr), height(ZERO) {}

    void updateHeight()
    {
        int left_height = (left_son != nullptr) ? left_son->height : -1;
        int right_height = (right_son != nullptr) ? right_son->height : -1;
        height = (left_height < right_height) ? right_height + 1 : left_height + 1;
    }

    int getBF()
    {
        int left_height = (left_son != nullptr) ? left_son->getHeight() : -1;
        int right_height = (right_son != nullptr) ? right_son->getHeight() : -1;
        return left_height - right_height;
    }
};

template <typename T, class Compare>
class AVLTree
{
public:
    shared_ptr<AVLTreeNode<T>> root;
    Compare comp; // true if second argument is greater than first

    AVLTree() : root(nullptr), comp(Compare()){};

    shared_ptr<AVLTreeNode<T>> find(shared_ptr<T> node);

    bool insert(const shared_ptr<T> &inner_node);

    bool remove(const shared_ptr<T> &inner_node);

private:
    shared_ptr<AVLTreeNode<T>> LL(shared_ptr<AVLTreeNode<T>> B);
    shared_ptr<AVLTreeNode<T>> RR(shared_ptr<AVLTreeNode<T>> A);
    shared_ptr<AVLTreeNode<T>> LR(shared_ptr<AVLTreeNode<T>> node);
    shared_ptr<AVLTreeNode<T>> RL(shared_ptr<AVLTreeNode<T>> node);
    shared_ptr<AVLTreeNode<T>> Rotate(shared_ptr<AVLTreeNode<T>> node);

    shared_ptr<AVLTreeNode<T>> insertRec(shared_ptr<AVLTreeNode<T>> node, const std::shared_ptr<AVLTreeNode<T>> &key)
    {
        if (comp(key, node->inner_node))
            node->left = insertRec(node->left, key);
        else if (comp(node->inner_node, key))
            node->right = insertRec(node->right, key);
        else // Equal keys are not allowed in AVL tree
            return node;

        node->updateHeight();

        int balance = node->getBF();
        if (balance == POSITIVE_UNBALANCED || balance == NEGATIVE_UNBALANCED)
        {
            return Rotate(node);
        }

        return node;
    }
};

template <typename T, class Compare>
bool AVLTree<T, Compare>::insert(const shared_ptr<T> &inner_node)
{
    auto node = make_shared<AVLTreeNode<T>>(inner_node);
    if (root == nullptr)
    {
        root = node;
        return true;
    }

    auto parent = find(inner_node);
    if (parent->inner_node == inner_node)
        return False;
    if (comp(parent->inner_node, inner_node))
    {
        parent->right = node;
    }
    else
    {
        parent->left = node;
    }
    node->parent = parent;

    while (parent != nullptr)
    {
        parent->updateHeight();
        if (parent->getBF() == POSITIVE_UNBALANCED || parent->getBF() == NEGATIVE_UNBALANCED)
        {
            parent = Rotate(parent);
            break;
        }
        node = parent;
        parent = parent->parent;
    }
    if (parent == nullptr)
        root = node;
    return true;
}

template <typename T, class Compare>
bool AVLTree<T, Compare>::remove(const shared_ptr<T> &inner_node)
{

    auto node = make_shared<AVLTreeNode<T>>(inner_node);
    if (root == nullptr)
    {
        root = node;
        return true;
    }

    auto parent = find(inner_node);
    if (parent->inner_node == inner_node)
        return False;
    if (comp(parent->inner_node, inner_node))
    {
        parent->right = node;
    }
    else
    {
        parent->left = node;
    }
    node->parent = parent;

    while (parent != nullptr)
    {
        parent->updateHeight();
        if (parent->getBF() == POSITIVE_UNBALANCED || parent->getBF() == NEGATIVE_UNBALANCED)
        {
            parent = Rotate(parent);
        }
        node = parent;
        parent = parent->parent;
    }
    root = node;
    return true;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::find(shared_ptr<T> node)
{
    shared_ptr<AVLTreeNode<T>> current = root;
    shared_ptr<AVLTreeNode<T>> previous = current;
    while (current != nullptr)
    {
        previous = current;
        if (comp(node, current->inner_node))
            current = current->left;
        else if (comp(current->inner_node, node))
            current = current->right;
        else
            return current;
    }
    return previous;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::LL(shared_ptr<AVLTreeNode<T>> B)
{
    auto A = B->left_son;
    auto AR = A->right_son;
    auto parent = B->parent;

    B->left_son = nullptr;
    A->right_son = B;

    B->left_son = AR;

    A->parent = parent;
    B->parent = A;
    if (AR)
        AR->parent = B;
    if (parent)
    {
        if (parent->left_son == B)
            parent->left_son = A;
        else
            parent->right_son = A;
    }

    B->updateHeight();
    A->updateHeight();

    return A;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::RR(shared_ptr<AVLTreeNode<T>> A)
{
    auto B = A->right_son;
    auto BL = B->left_son;
    auto parent = A->parent;

    A->right_son = nullptr;
    B->left_son = A;

    A->right_son = BL;

    B->parent = parent;
    A->parent = B;
    if (BL)
        BL->parent = A;
    if (parent)
    {
        if (parent->left_son == A)
            parent->left_son = B;
        else
            parent->right_son = B;
    }

    A->updateHeight();
    B->updateHeight();

    return B;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::LR(shared_ptr<AVLTreeNode<T>> node)
{
    node->left = rightRotate(node->left);
    return leftRotate(node);
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::RL(shared_ptr<AVLTreeNode<T>> node)
{
    node->right = leftRotate(node->right);
    return rightRotate(node);
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::Rotate(shared_ptr<AVLTreeNode<T>> node)
{
    if (node->getBF() == 2)
    {
        if (node->left->getBF() >= 0)
            return LL(node);
        else
            return LR(node);
    }
    else
    {
        if (node->right->getBF() <= 0)
            return RR(node);
        else
            return RL(node);
    }
}
