#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>

#define vec std::vector<int>

int partition(vec& v, int p, int r) {
    int x = v[r], i = p - 1;
    for (int j = p; j < r; ++j)
        if (v[j] <= x)
        {
            ++i;
            std::swap(v[i], v[j]);
        }
    std::swap(v[i + 1], v[r]);
    return i + 1;
}

void quicksort(vec& v, int p, int r) {
    if (p < r)
    {
        int q = partition(v, p, r);
        quicksort(v, p, q - 1);
        quicksort(v, q + 1, r);
    }
}

int main() {

    std::vector<vec> cases = {
            { 12, 3, 6, 1, 9, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3},
            { 12, 3, 6, 1, 7, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3, 12, 3, 6, 1, 7, 9, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3},
            { 1 },
            { 6, 3 },
            { 6, 3, 6 },
            { 6, 3, 2, 6 }
    };

    for (auto& input : cases)
    {
        quicksort(input, 0, input.size() - 1);
        std::cout << std::is_sorted(input.begin(), input.end()) << std::endl;
    }

    return 0;
}
