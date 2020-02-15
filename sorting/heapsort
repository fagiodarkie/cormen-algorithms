#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>

struct heap
{
    explicit heap(std::vector<int> v) : numbers(std::move(v)) {}

    std::vector<int> numbers;
    static unsigned int parent(int i) {
        return (i + 1)  / 2 - 1;
    }

    static unsigned int left(int i) {
        return 2 * (i + 1) - 1;
    }

    static unsigned int right(int i) {
        return 2 * (i + 1);
    }
    int operator[](unsigned int i) const {
        return numbers[i];
    }

    int& operator[](unsigned int i) {
        return numbers[i];
    }
};

auto MAX_HEAP_PROPERTY = [] (const heap& h, int i) {
    return h[heap::parent(i)] >= h[i];
};

auto MIN_HEAP_PROPERTY = [] (const heap& h, int i) {
    return h[heap::parent(i)] <= h[i];
};

std::function<bool(int, int)> MAX_HEAP_CONDITION = [](const int a, const int b) { return a > b; };
std::function<bool(int, int)> MIN_HEAP_CONDITION = [](const int a, const int b) { return a < b; };

void heapify(heap& h, unsigned int i, std::function<bool(int, int)>& condition, unsigned int size) {
    auto l = heap::left(i), r = heap::right(i);
    auto extreme = (l < size && condition(h[l], h[i])) ? l : i;
    extreme = (r < size && condition(h[r], h[extreme])) ? r : extreme;
    do {
        if (extreme != i)
            std::swap(h[i], h[extreme]);

        i = extreme;

        l = heap::left(i), r = heap::right(i);
        extreme = (l < size && condition(h[l], h[i])) ? l : i;
        extreme = (r < size && condition(h[r], h[extreme])) ? r : extreme;
    }
    while (extreme != i);
}

heap buildHeap(std::vector<int>& a, std::function<bool(int, int)>& condition) {
    heap result(a);
    for (int i = a.size() / 2; i >= 0; --i)
        heapify(result, i, condition, a.size());
    return result;
}

void heapsort(std::vector<int>& v)
{
    auto heap = buildHeap(v, MAX_HEAP_CONDITION);
    for (int i = v.size() - 1; i > 0;  --i)
    {
        std::swap(heap[0], heap[i]);
        heapify(heap, 0, MAX_HEAP_CONDITION, i);
    }
    v.swap(heap.numbers);
}

int main() {

    std::vector<int> item =
            { 1, 894, -5, 3, 5, 7, 3, 9, 34, 245, 23, 6, -5, 4, -34, 23, 1, 54, 1, 6, 24};

    heapsort(item);

    std::cout << std::is_sorted(item.begin(), item.end()) << std::endl;

    return 0;
}
