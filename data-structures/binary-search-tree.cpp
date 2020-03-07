#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <numeric>

enum class traverseType
{
    preorder,
    inorder,
    postorder
};

class binarySearchTree
{
public:
    binarySearchTree(int value, binarySearchTree* parent = nullptr)
        : p(parent), left(nullptr), right(nullptr), _value(value)
    { }

    ~binarySearchTree()
    {
        delete left;
        delete right;
    }

    void insert(int x)
    {
        if (x <= _value)
        {
            if (!left)
                left = new binarySearchTree(x, this);
            else left->insert(x);
        }
        else
        {
            if (!right)
                right = new binarySearchTree(x, this);
            else right->insert(x);
        }
    }

    void perform(traverseType t, std::function<void(int)>& f)
    {
        switch(t)
        {
            case traverseType::preorder:
                if (left)
                    left->perform(t, f);
                if (right)
                    right->perform(t, f);
                f(_value);
            case traverseType::postorder:
                f(_value);
                if (left)
                    left->perform(t, f);
                if (right)
                    right->perform(t, f);
            case traverseType::inorder:
                if (left)
                    left->perform(t, f);
                f(_value);
                if (right)
                    right->perform(t, f);
        }
    }

    bool has(traverseType t, int x)
    {
        switch(t)
        {
            case traverseType::preorder:
                if (left && left->has(t, x))
                    return true;
                if (right && right->has(t, x))
                    return true;
                return _value == x;
            case traverseType::postorder:
                if (_value == x)
                    return true;
                if (left && left->has(t, x))
                    return true;
                return (right && right->has(t, x));
            case traverseType::inorder:
                if (left && left->has(t, x))
                    return true;
                if (_value == x)
                    return true;
                return (right && right->has(t, x));
        }
    }

private:
    binarySearchTree *p, *left, *right;
    int _value;
};

int main() {

    std::vector<int> cases = { 1, 5, 3, 7, 2, 7, 3, 9, 2, 6, 2, 6, 7, 9, 5, 1, 7, 4 };
    binarySearchTree *S = new binarySearchTree(5);

    for (auto i : cases) {
        S->insert(i);
    }

    for (auto i : cases) {
        if (!S->has(traverseType::inorder, i))
            return 1;
    }

    std::function<void(int)> print = [](int x) { std::cout << x << " "; };

    S->perform(traverseType::inorder, print);

    return 0;
}
