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
    stack() : _queue(new T[10]), _queueSize(10), _head(0), _size(0) {};
    ~stack() { delete[] _queue; }

    void enqueue(T x)
    {
        // enlarge
        if (_size == _queueSize)
        {
            int newQueueSize = _queueSize * 2;
            T* newQueue = new T[newQueueSize];
            for (int i = 0; i < _queueSize; ++i)
            {
                newQueue[i] = _at(_head++);
            }

            _head = 0;
            delete [] _queue;
            _queue = newQueue;
            _queueSize = newQueueSize;
        }

        _queue[_size] = x;
        ++_size;
    }

    void dequeue()
    {
        if (empty())
            throw "underflow";
        increase(_head);
        --_size;
    }

    T& head()
    {
        if (empty())
            throw "underflow";
        return _queue[_head];
    }

    bool empty() const
    {
        return _size == 0;
    }

    int size() const
    {
        return _size;
    }

private:
    T* _queue;
    unsigned int _queueSize, _head, _size;

    int tail() const
    {
        return (_head + _size) % _queueSize
    }

    T& _at(unsigned int i)
    {
        return _queue[i % _queueSize];
    }

    void increase(unsigned int& i)
    {
        i = (i + 1) % _queueSize;
    }
};

int main() {

    std::vector<int> cases = { 12, 3, 6, 1, 9, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 42, 3};
    stack<int> S;

    for (int i : cases) {
        S.enqueue(i);
    }
    for (int i : cases) {
        if (S.head() != i)
            return 1;
        S.dequeue();
    }

    return 0;
}
