#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

std::string str(std::vector<int> input)
{
    std::stringstream ss;
    for (int i: input) ss << i << " ";
    return ss.str();
}

int find(int item, const std::vector<int>& v, int begin, int end)
{
    if (begin == end) return -1;
    
    if (begin + 1 == end)
    {
        return v[begin] == item ? begin : -1;
    }

    int half = begin + (end - begin) / 2;
    if (v[half] == item)
        return (begin + end) / 2;
    else if (v[half] > item)
        return find(item, v, begin, half);
    else
        return find(item, v, half, end);


}

int find(const std::vector<int>& v, int item)
{
    return find(item, v, 0, v.size());
}

int main() {

    std::vector<int> item =
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};

    std::vector<int> search = {1, 22, 4, 7, 2, 5};

    for (const auto& input : search)
    {
        auto result = find(item, input);
        std::cout << (result == (std::find(item.begin(), item.end(), input) - item.begin())) << std::endl;
    }


    return 0;
}
