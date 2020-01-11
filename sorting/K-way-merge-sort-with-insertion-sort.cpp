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

const int K = 4;

std::string str(std::vector<int> input)
{
    std::stringstream ss;
    for (int i: input) ss << i << " ";
    return ss.str();
}

void merge (std::vector<int>& vector, int p, int r)
{
    std::vector<std::vector<int>> L;
    for (auto i = p; i < r; i += K)
    {
        std::vector<int> v;
        for (auto j = 0; j < K && (i + j < r); ++j)
            v.push_back(vector[i+j]);
        L.emplace_back(v);
    }

    for (int i = p; i < r; ++i)
    {
        int min = INT_MAX;
        std::vector<int>& array = L[0];
        for (auto arr: L)
        {
            if (arr.begin() != arr.end() && (*arr.begin() < min))
            {
                min = *arr.begin();
                array = arr;
            }
        }
        vector[i] = min;
        array.erase(array.begin());
    }

}

void inssort(std::vector<int>& input, int begin, int end)
{
    for (int i = begin + 1; i < end; ++i)
    {
        int j = i;
        while (j > 0 && input[j - 1] > input[i])
            --j;

        int removed = input[i];
        input.erase(input.begin() + i);
        input.insert(input.begin() + j, removed);
    }
}

void sort(std::vector<int>& input, int begin, int end)
{
    if (end == begin + 1)
        return;

    if (end - begin <= K)
    {
        inssort(input, begin, end);
        return;
    }

    // this average avoids overflows
    if (end - begin > K)
    {
        for (int i = begin; i < end; i += K)
        {
            inssort(input, i, std::min(i + K, end));
        }
    }
    merge(input, begin, end);
}

std::vector<int> sort(const std::vector<int>& in)
{
    auto result = in;

    sort (result, 0, result.size());

    return result;
}

int main() {

    std::vector<std::vector<int>> cases = {
            { 12, 3, 6, 1, 9, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3},
            { 12, 3, 6, 1, 7, 3, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3, 12, 3, 6, 1, 7, 9, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3},
            { 1 },
            { 6, 3 },
            { 6, 3, 6 },
            { 6, 3, 2, 6 }
    };

    for (const auto& input : cases)
    {
        auto result = sort(input);
        std::cout << std::is_sorted(result.begin(), result.end()) << std::endl;
    }


    return 0;
}
