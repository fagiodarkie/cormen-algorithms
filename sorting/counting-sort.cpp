#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>

#define vec std::vector<int>

int nextInt(vec& x, int currentIndex) {
    while (x[currentIndex] == 0)
        ++ currentIndex;

    -- x[currentIndex];
    return currentIndex;
}

void countingSort(vec& v, int k) {
    vec C(k + 1, 0);
    for (auto i: v) {
        if (i > k)
            throw std::exception();

        ++C[i];
    }

    vec res;
    int index = 0;
    for (int i = 0; i < v.size(); ++i)
        res.emplace_back(nextInt(C, index));

    v.swap(res);
}

int main() {

    std::vector<vec> cases = {
            { 12, 3, 6, 1, 9, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 42, 3},
            { 12, 3, 6, 1, 7, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 42, 3, 12, 3, 6, 1, 7, 9, 23, 6, 4, 4, 12, 59, 4, 2, 22, 42, 3},
            { 1 },
            { 6, 3 },
            { 6, 3, 6 },
            { 6, 3, 2, 6 }
    };

    vec caseSize = {
            59,
            59,
            1,
            6,
            6,
            6
    };

    for (int i = 0; i < cases.size(); ++i)
    {
        countingSort(cases[i], caseSize[i]);
        std::cout << std::is_sorted(cases[i].begin(), cases[i].end()) << std::endl;
    }

    return 0;
}
