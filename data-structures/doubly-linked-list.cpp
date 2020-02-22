#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <numeric>

template <typename T>
class doublyLinkedList
{
public:
    template <typename T>
    class listElement {
        friend class doublyLinkedList<T>;
    public:
        T item;

        listElement(T newItem, listElement<T> *prev = nullptr, listElement<T> *nxt = nullptr) : item(newItem), previous(prev), next(nxt) {}

    private:
        listElement<T> *previous, *next;
    };

    doublyLinkedList() : _size(0), _head(nullptr), _tail(nullptr) {};
    ~doublyLinkedList()
    {
        listElement<T> *current = _head, *next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(T x)
    {
        insert(x, _size);
    }

    void insert(T x, int i)
    {
        if (empty())
        {
            _head = new  listElement<T>(x);
            _tail = _head;
            _size = 1;
            return;
        }

        if (i == 0)
        {
            _head->previous = new listElement<T>(x, nullptr, _head);
            _head = _head->previous;
            ++_size;
            return;
        }

        if (i == _size)
        {
            _tail->next = new listElement<T>(x, _tail);
            _tail = _tail->next;
            ++_size;
            return;
        }

        listElement<T> *insertPoint = findInsertPoint(i), *insertNext;

        insertNext = insertPoint->next;
        insertPoint->next = new listElement<T>(x, insertPoint, insertNext);
        insertNext->previous = insertPoint->next;
        ++_size;
    }

    void remove(int i)
    {
        if (empty())
            throw "underflow";

        if (i == 0)
        {
            auto tmp = _head;
            _head = _head->next;
            delete tmp;
        }
        else if (i == _size - 1)
        {
            auto tmp = _tail;
            _tail = _tail->previous;
            delete tmp;
        } else
        {
            auto tmp = findInsertPoint(i), tmpPrev = tmp->previous;
            tmpPrev->next = tmp->next;
            delete tmp;
        }
        --_size;
    }

    T& head()
    {
        if (empty())
            throw "underflow";
        return _head->item;
    }

    T& tail()
    {
        if (empty())
            throw "underflow";
        return _tail->item;
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
    listElement<T> *_head, *_tail;
    unsigned int _size;

    listElement<T>* findInsertPoint(int i) const
    {
        listElement<T>* insertPoint;
        if (i > (_size / 2))
        {
            insertPoint = _tail;
            while (i++ < _size)
                insertPoint = insertPoint->previous;
        } else {
            insertPoint = _head;
            while (i-- > 0)
                insertPoint = insertPoint->next;
        }
        return insertPoint;
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
    doublyLinkedList<int> S;

    for (int i : cases) {
        S.insert(i);
    }
    for (int i : cases) {
        if (S.head() != i)
            return 1;
        S.remove(0);
    }

    return 0;
}
