#include <map>
#include <string>
#include <iostream>

using namespace std;

struct entry {
    string name;
    unsigned quantity;
};

int main()
{
    const entry array[] = {
        { "apple", 5 },
        { "pear",  2 },
        { "grape", 6 },
        { "mango", 3 },
        { "apple", 2 },
        { "mango", 9 },
    };

    map<string, unsigned> m;
    for (auto& e : array)
        m[e.name] += e.quantity;

    for (auto& e : m)
        cout << e.first << " " << e.second << "\n";
}