#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <iostream>

struct Room {
    std::string name;
    std::string initial;
    int n1;
    int n2;
};

bool comp(const Room& r1, const Room& r2)
{
    return
        std::tie(r1.name, r1.initial, r1.n1, r1.n2) <
        std::tie(r2.name, r2.initial, r2.n1, r2.n2);
}

bool searchRoom(const std::vector<Room>& v, const Room& r)
{
    return std::binary_search(begin(v), end(v), r, comp);
}

int main()
{
   std::vector<Room> v;
   std::cout << searchRoom( v, { "name", "init", 1, 2 } );
}