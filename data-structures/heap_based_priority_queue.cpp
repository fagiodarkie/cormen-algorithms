#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>

struct S {
    S(int a, char b) : k(a), v(b) {}
    int k;
    char v;
};

struct heap
{
    heap(std::vector<S> v, std::function<bool(S, S)>& condition) : numbers(std::move(v)), heap_condition(condition) {
        for (int i = numbers.size() / 2; i >= 0; --i)
            heapify(i, numbers.size());
    }

    const std::function<bool(S, S)> heap_condition;
    std::vector<S> numbers;
    static unsigned int parent(int i) {
        return (i + 1)  / 2 - 1;
    }

    static unsigned int left(int i) {
        return 2 * (i + 1) - 1;
    }

    void heapify(unsigned int i, unsigned int size) {
        auto l = heap::left(i), r = heap::right(i);
        auto extreme = (l < size && heap_condition(numbers[l], numbers[i])) ? l : i;
        extreme = (r < size && heap_condition(numbers[r], numbers[extreme])) ? r : extreme;
        do {
            if (extreme != i)
                std::swap(numbers[i], numbers[extreme]);

            i = extreme;

            l = heap::left(i), r = heap::right(i);
            extreme = (l < size && heap_condition(numbers[l], numbers[i])) ? l : i;
            extreme = (r < size && heap_condition(numbers[r], numbers[extreme])) ? r : extreme;
        }
        while (extreme != i);
    }

    void changeKey(int index, int newK) {

        numbers[index].k = newK;
        bool extremerThanParent = heap_condition(numbers[index], numbers[parent(index)]);

        if (extremerThanParent)
            while (index > 0 && !heap_condition(numbers[parent(index)], numbers[index]))
            {
                std::swap(numbers[index], numbers[parent(index)]);
                index = parent(index);
            }
        else heapify(index, numbers.size());
    }

    S top() const {
        return numbers[0];
    }

    void insert(char s, int k) {
        numbers.emplace_back(S(0, s));
        changeKey(numbers.size() - 1, k);
    }

    S pop() {
        auto res = numbers[0];
        std::swap(numbers[0], numbers[numbers.size() - 1]);
        numbers.erase(numbers.begin() + numbers.size() - 1);
        heapify(0, numbers.size());
    }

    static unsigned int right(int i) {
        return 2 * (i + 1);
    }
    S operator[](unsigned int i) const {
        return numbers[i];
    }

    S& operator[](unsigned int i) {
        return numbers[i];
    }
};

auto MAX_HEAP_PROPERTY = [] (const heap& h, int i) {
    return h[heap::parent(i)].k >= h[i].k;
};

auto MIN_HEAP_PROPERTY = [] (const heap& h, int i) {
    return h[heap::parent(i)].k <= h[i].k;
};

std::function<bool(S, S)> MAX_HEAP_CONDITION = [](const S a, const S b) { return a.k > b.k; };
std::function<bool(S, S)> MIN_HEAP_CONDITION = [](const S a, const S b) { return a.k < b.k; };

void heapsort(std::vector<S>& v)
{
    heap new_heap(v, MAX_HEAP_CONDITION);
    for (int i = v.size() - 1; i > 0;  --i)
    {
        std::swap(new_heap[0], new_heap[i]);
        new_heap.heapify(0, i);
    }
    v.swap(new_heap.numbers);
}

int main() {

    std::vector<S> item =
            { { 1, 'a' }, { 894, 'b' }, { -52, 'c' }, { 3, 'd' }, { 5, 'e' }, { 7, 'f' }, { 31, 'g' }, { 9, 'h' },
              { 34, 'i' }, { 245, 'j' }, { 231, 'k' }, { 6, 'l' }, { -54, 'm' }, { 4, 'n' }, { -34, 'o' },
              { 23, 'p' }, { 11, 'q' }, { 54, 'r' }, { 12, 's' }, { 63, 't' }, { 24, 'u' } };

    heap h(item, MAX_HEAP_CONDITION);

    std::cout << (h.top().v == 'b') << std::endl;
    auto newTop = h.numbers[6].v;
    h.changeKey(6, 1024);
    std::cout << (h.top().v == newTop) << std::endl;
    h.insert('z', 2000);
    std::cout << (h.top().v == 'z') << std::endl;

    return 0;
}
