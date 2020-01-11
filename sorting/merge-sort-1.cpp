#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

void swap (std::vector<int>::iterator a, std::vector<int>::iterator b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

std::string str(std::vector<int> input)
{
    std::stringstream ss;
    for (int i: input) ss << i << " ";
    return ss.str();
}

void merge (std::vector<int>& vector, int p, int q, int r)
{
    std::vector<int> L1, L2;
    for (auto i = vector.begin() + p; i < vector.begin() + q; ++i)
        L1.push_back(*i);
    L1.push_back(INT_MAX);

    for (auto i = vector.begin() + q; i < vector.begin() + r; ++i)
        L2.push_back(*i);
    L2.push_back(INT_MAX);

    int i1 = 0, i2 = 0;
    for (int i = p; i < r;)
    {
        if (L1[i1] < L2[i2] && L1[i1] != INT_MAX)
        {
            vector[i] = L1[i1];
            ++i1;
            ++i;
        } else if (L2[i2] != INT_MAX)
        {
            vector[i] = L2[i2];
            ++i2;
            ++i;
        }

    }

}

void sort(std::vector<int>& input, int begin, int end)
{
    if (end == begin + 1)
        return;

    // this average avoids overflows
    int mid = begin + ((end - begin) / 2);
    sort (input, begin, mid);
    sort (input, mid, end);
    merge(input, begin, mid, end);
}

std::vector<int> sort(const std::vector<int>& in)
{
    auto result = in;

    sort (result, 0, result.size());

    return result;
}

int main() {

    std::vector<std::vector<int>> cases = {
            { 12, 3, 6, 1, 7, 9, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3},
            { 1 },
            { 6, 3 }
    };
    for (const auto input : cases)
    {
        auto result = sort(input);
        std::cout << std::is_sorted(result.begin(), result.end()) << std::endl;
    }


    return 0;
}
