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
    weak_ptr<AVLTreeNode<T>> parent;
    weak_ptr<AVLTreeNode<T>> max_Id;
    int height;

    AVLTreeNode(const shared_ptr<T> &node)
        : inner_node(node), left_son(nullptr), right_son(nullptr), parent(nullptr), height(ZERO) {}

    void updateHeight()
    {
        int left_height = (left_son != nullptr) ? left_son->height : -1;
        int right_height = (right_son != nullptr) ? right_son->height : -1;
        height = (left_height < right_height) ? right_height + 1 : left_height + 1;
    }

    int getBF() const
    {
        int left_height = (left_son != nullptr) ? left_son->getHeight() : -1;
        int right_height = (right_son != nullptr) ? right_son->getHeight() : -1;
        return left_height - right_height;
    }

    void removeOnlyChild()
    {
        shared_ptr<AVLTreeNode<T>> temp;
        if (node->left == nullptr && node->right == nullptr)
        {
            temp = nullptr:
        }
        else if (node->left == nullptr)
        {
            temp = node->right;
        }
        else
        {
            temp = node->left;
        }

        if (parent == nullptr)
        {
            root = temp;
        }
        else
        {
            if (parent->left == node)
                parent->left = temp;
            else
                parent->right = temp;

            temp->parent = parent;
        }
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

    void inOrder(shared_ptr<AVLTreeNode<T>> node) const;
    void preOrder(shared_ptr<AVLTreeNode<T>> node) const;
    void postOrder(shared_ptr<AVLTreeNode<T>> node) const;

private:
    shared_ptr<AVLTreeNode<T>> LL(shared_ptr<AVLTreeNode<T>> B);
    shared_ptr<AVLTreeNode<T>> RR(shared_ptr<AVLTreeNode<T>> A);
    shared_ptr<AVLTreeNode<T>> LR(shared_ptr<AVLTreeNode<T>> node);
    shared_ptr<AVLTreeNode<T>> RL(shared_ptr<AVLTreeNode<T>> node);
    shared_ptr<AVLTreeNode<T>> Rotate(shared_ptr<AVLTreeNode<T>> node);

    shared_ptr<AVLTreeNode<T>> nextNode(shared_ptr<AVLTreeNode<T>> node)
    {
        auto Next = node->right;
        while (Next->left != nullptr)
        {
            Next = Next->left;
        }
        return Next;
    }

    void updateMaxId(shared_ptr<AVLTreeNode<T>> node)
    {
        shared_ptr<AVLTreeNode<T>> left_max = (left_son != nullptr) ? left_son->max_Id.lock() : nullptr;
        shared_ptr<AVLTreeNode<T>> right_max = (right_son != nullptr) ? right_son->max_Id.lock() : nullptr;
        shared_ptr<AVLTreeNode<T>> max = node;
        if (left_max != nullptr && comp(max->inner_node, left_max->inner_node))
            max = left_max;
        if (right_max != nullptr && comp(max->inner_node, right_max->inner_node))
            max = right_max;
        node->max_Id = max;
    }
    void updateData(shared_ptr<AVLTreeNode<T>> node)
    {
        node->updateHeight();
        updateMaxId(node);
    }
};

template <typename T, class Compare>
void AVLTree<T, Compare>::inOrder(shared_ptr<AVLTreeNode<T>> node) const
{
    if (node == nullptr)
    {
        return;
    }
    inOrder(node->getLeftSon());
    cout << *(node->inner_node);
    inOrder(node->getRightSon());
}

template <typename T, class Compare>
void AVLTree<T, Compare>::preOrder(shared_ptr<AVLTreeNode<T>> node) const
{
    if (node == nullptr)
    {
        return;
    }
    cout << *(node->inner_node);
    preOrder(node->getLeftSon());
    preOrder(node->getRightSon());
}

template <typename T, class Compare>
void AVLTree<T, Compare>::postOrder(shared_ptr<AVLTreeNode<T>> node) const
{
    if (node == nullptr)
    {
        return;
    }
    cout << *(node->inner_node);
    postOrder(node->getLeftSon());
    postOrder(node->getRightSon());
}

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
        parent->updateData();
        if (parent->getBF() == POSITIVE_UNBALANCED || parent->getBF() == NEGATIVE_UNBALANCED)
        {
            parent = Rotate(parent);
        }
        node = parent;
        parent = parent->parent.lock();
    }
    root = node;
    return true;
}

template <typename T, class Compare>
bool AVLTree<T, Compare>::remove(const shared_ptr<T> &inner_node)
{
    if (root == nullptr)
    {
        return false;
    }

    auto node = find(inner_node);
    if (node->inner_node != inner_node)
        return False;

    if (node->left == nullptr || node->right == nullptr)
    {
        node->removeOnlychild();
    }
    else
    {
        auto next = nextNode(node);
        node->inner_node = next->inner_node;
        node = next;
        node->removeOnlychild();
    }

    auto parent = node->parent.lock();

    while (parent != nullptr)
    {
        parent->updateData();
        if (parent->getBF() == POSITIVE_UNBALANCED || parent->getBF() == NEGATIVE_UNBALANCED)
        {
            parent = Rotate(parent);
        }
        node = parent;
        parent = parent->parent.lock();
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
    auto parent = B->parent.lock();

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
        parent->updateData();
    }

    B->updateData();
    A->updateData();

    return A;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::RR(shared_ptr<AVLTreeNode<T>> A)
{
    auto B = A->right_son;
    auto BL = B->left_son;
    auto parent = A->parent.lock();

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

    A->updateData();
    B->updateData();

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
