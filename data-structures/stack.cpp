#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <numeric>

template <typename T>
class stack
{
public:
    stack() : _stack(new T[10]), _stackSize(10), _currentElement(0) {};
    ~stack() { delete[] _stack; }

    void push(T x)
    {
        if (_currentElement == _stackSize)
        {
            int* newStack = new int[2 * _stackSize];
            for (unsigned int i = 0; i < _stackSize; ++i)
                newStack[i] = _stack[i];

            _stackSize *= 2;
            delete[] _stack;
            _stack = newStack;
        }
        _stack[_currentElement++] = x;
    }

    void pop()
    {
        if (_currentElement > 0)
            --_currentElement;
    }

    T& top()
    {
        if (_currentElement > 0)
            return _stack[_currentElement - 1];
        throw "underflow error";
    }

    bool empty() const
    {
        return _currentElement == 0;
    }

private:
    T* _stack;
    unsigned int _stackSize, _currentElement;
};

int main() {

    std::vector<int> cases = { 12, 3, 6, 1, 9, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 42, 3};
    stack<int> S;

    for (int i : cases)
    {
        S.push(i);
        if (S.top() != i)
            return 1;
    }

    return 0;
}
