#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <numeric>

typedef std::vector<int> vec;

void insertionSort(vec& in)
{
    auto result = in;

    for (int i = 1; i < result.size(); ++i)
    {
        int j = i;
        while (j > 0 && result[j - 1] > result[i])
            --j;

        if (j < i)
        {
            int removed = result[i];
            result.erase(result.begin() + i);
            result.insert(result.begin() + j, removed);
        }
    }

    in.swap(result);
}

int bucketNumber(int value) { return value / 10; }

void bucketSort(vec& v) {
    std::vector<vec> buckets(10);
    vec res;

    for (auto i: v)
        buckets[bucketNumber(i)].emplace_back(i);

    for (auto& vs: buckets)
    {
        insertionSort(vs);
        for (auto i: vs)
            res.emplace_back(i);
    }

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

    for (int i = 0; i < cases.size(); ++i)
    {
        bucketSort(cases[i]);
        std::cout << std::is_sorted(cases[i].begin(), cases[i].end()) << std::endl;
    }

    return 0;
}
