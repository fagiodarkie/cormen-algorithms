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

std::vector<int> sort(const std::vector<int>& in)
{
    auto result = in;

    for (int i = 1; i < result.size(); ++i)
    {
        for (int j = i - 1; j >= 0; --j)
            if (result[j] > result[j + 1])
                swap(result.begin() + j + 1, result.begin() + j);
            else
                continue;
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
