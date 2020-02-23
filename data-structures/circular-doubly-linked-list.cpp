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

    doublyLinkedList() : _nil(new listElement<T>(T())) { _nil->next = _nil->previous = _nil; }
    ~doublyLinkedList()
    {
        listElement<T> *current = _nil, *next = nullptr;
        _nil->previous->next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(T x)
    {
        listElement<T> *insertPoint = _nil->previous;

        insertPoint->next = new listElement<T>(x, insertPoint, _nil);
        _nil->previous = insertPoint->next;
    }

    void remove()
    {
        if (empty())
            throw "underflow";

        auto tmp = _nil->next;
        _nil->next = tmp->next;
        tmp->next->previous = _nil;
        delete tmp;
    }

    T& head()
    {
        if (empty())
            throw "underflow";
        return _nil->next->item;
    }

    T& tail()
    {
        if (empty())
            throw "underflow";
        return _nil->previous->item;
    }

    bool empty() const
    {
        return _nil->next == _nil;
    }

private:
    listElement<T> *_nil;
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
        S.remove();
    }

    return 0;
}
