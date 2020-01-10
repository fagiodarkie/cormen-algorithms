#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> sort(const std::vector<int>& in)
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

    return result;
}


int main() {

    std::vector<std::vector<int>> cases = {
            { 12, 3, 6, 1, 7, 9, 23, 6, 4, 4, 12, 59, 4, 2, 22, 492, 3},
            { 1 },
            { 3, 6 }
    };
    for (const auto input : cases)
    {
        auto result = sort(input);
        std::cout << std::is_sorted(result.begin(), result.end()) << std::endl;
    }


    return 0;
}
