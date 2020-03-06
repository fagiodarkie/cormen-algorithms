#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <numeric>

class stringChainedHashMap
{
public:
    stringChainedHashMap()
    {
        _map = std::vector<std::vector<std::string>>(10, std::vector<std::string>());
    }

    void insert(const std::string& x)
    {
        _map[hash(x)].push_back(x);
    }

    bool has(const std::string& x) const
    {
        if (empty())
            return false;

        return find(x) != _map[hash(x)].end();
    }

    void remove(const std::string& x)
    {
        if (!has(x))
            return;

        _map[hash(x)].erase(find(x));
    }

    bool empty() const
    {
        for (auto v: _map)
            if (!v.empty())
                return false;
        return true;
    }

private:
    std::vector<std::vector<std::string>> _map;

    static int hash(const std::string& s)
    {
        return s.size() % 10;
    }

    std::vector<std::string>::iterator find(const std::string& x)
    {
        return std::find(_map[hash(x)].begin(), _map[hash(x)].end(), x);
    }

    std::vector<std::string>::const_iterator find(const std::string& x) const
    {
        return std::find(_map[hash(x)].begin(), _map[hash(x)].end(), x);
    }
};

int main() {

    std::vector<std::string> cases = { "a", "aa", "asj", "asofoaskaksoabga", "kjdadjf", "asjfaisjfa", "asjfasifjba", "a", "askgeka", "idfgja" };
    stringChainedHashMap S;

    for (auto i : cases) {
        S.insert(i);
    }

    for (auto i : cases) {
        if (!S.has(i))
            return 1;
    }

    return 0;
}
