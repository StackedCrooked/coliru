#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct entry {
    string name;
    unsigned quantity;
};

vector<entry> consolidate(vector<entry> const& in)
{
    vector<entry> result;

    for (auto& e : in)
    {
        auto found = find_if(begin(result), end(result), [&e](entry const& a) { return a.name == e.name; });
        if (end(result) == found)
            result.push_back(e);
        else
            found->quantity += e.quantity;
    }

    return result;
}

int main()
{
    const vector<entry> array {
        { "apple", 5 },
        { "pear",  2 },
        { "grape", 6 },
        { "mango", 3 },
        { "apple", 2 },
        { "mango", 9 },
    };

    auto cons = consolidate(array);

    for (auto& e : cons)
        cout << e.name << " " << e.quantity << "\n";
}
