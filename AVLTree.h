#include <memory>
#include "pirates24b1.h"

using namespace std;

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
    Compare comp;

    AVLTree() : root(nullptr), comp(Compare()) {}

    void insert(const shared_ptr<T> &inner_node)
    {
        root = insertRec(root, key);
    }

    void remove(const shared_ptr<T> &inner_node)
    {
        root = insertRec(root, key);
    }

private:
    shared_ptr<AVLTreeNode<T>> LL(std::shared_ptr<AVLTreeNode<T>> B)
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

    shared_ptr<AVLTreeNode<T>> RR(std::shared_ptr<AVLTreeNode<T>> A)
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

    shared_ptr<AVLTreeNode<T>> LR(std::shared_ptr<AVLTreeNode<T>> node)
    {
        node->left = rightRotate(node->left);
        return leftRotate(node);
    }

    shared_ptr<AVLTreeNode<T>> RL(std::shared_ptr<AVLTreeNode<T>> node)
    {
        node->right = leftRotate(node->right);
        return rightRotate(node);
    }

    std::shared_ptr<AVLTreeNode<T>> insertRec(std::shared_ptr<AVLTreeNode<T>> node, const std::shared_ptr<AVLTreeNode<T>> &key)
    {
        if (!node)
            return key;

        if (comp(key, node))
            node->left = insertRec(node->left, key);
        else if (comp(node, key))
            node->right = insertRec(node->right, key);
        else // Equal keys are not allowed in AVL tree
            return node;

        // Update height of this ancestor node
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && comp(key, node->left))
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && comp(node->right, key))
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && comp(node->left, key))
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && comp(key, node->right))
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }
};
