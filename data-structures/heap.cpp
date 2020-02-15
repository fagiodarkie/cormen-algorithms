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

void heapify(heap& h, unsigned int i, std::function<bool(int, int)>& condition) {
    auto l = heap::left(i), r = heap::right(i);
    auto extreme = (l < h.numbers.size() && condition(h[l], h[i])) ? l : i;
    extreme = (r < h.numbers.size() && condition(h[r], h[extreme])) ? r : extreme;
    do {
        if (extreme != i)
            std::swap(h[i], h[extreme]);

        i = extreme;

        l = heap::left(i), r = heap::right(i);
        extreme = (l < h.numbers.size() && condition(h[l], h[i])) ? l : i;
        extreme = (r < h.numbers.size() && condition(h[r], h[extreme])) ? r : extreme;
    }
    while (extreme != i);
}

heap buildHeap(std::vector<int>& a, std::function<bool(int, int)>& condition) {
    heap result(a);
    for (int i = a.size() / 2; i >= 0; --i)
        heapify(result, i, condition);
    return result;
}


int main() {

    std::vector<int> item =
            { 1, 894, -5, 3, 5, 7, 3, 9, 34, 245, 23, 6, -5, 4, -34, 23, 1, 54, 1, 6, 24};

    auto max_result = buildHeap(item, MAX_HEAP_CONDITION), min_result = buildHeap(item, MIN_HEAP_CONDITION);

    auto sorted_max = true, sorted_min = true;
    for (unsigned int i = 1; i < item.size(); ++i) {
        sorted_max &= MAX_HEAP_PROPERTY(max_result, i);
        sorted_min &= MIN_HEAP_PROPERTY(min_result, i);
    }

    std::cout << sorted_max << sorted_min << std::endl;

    return 0;
}
