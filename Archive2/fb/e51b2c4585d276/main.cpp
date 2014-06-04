#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

struct SomeCustomId { 
    int id;
    operator int() const { return id; }
    SomeCustomId() : id(0) {}
    SomeCustomId(int c)  : id(c) { }
};

struct mycomparer {
    bool operator()(string const& lhs, pair<string const, SomeCustomId> const& rhs) {
        return lhs < rhs.first;
    }
    bool operator()(pair<string const, SomeCustomId> const& lhs, string const& rhs) {
        return lhs.first < rhs;
    }
};
int main()
{
    vector<string> custom_list{ "test3", "test1"};
    map<string, SomeCustomId> master_list;
    vector<string> target_list;
    master_list["test1"] = 1;
    master_list["test2"] = 2;
    master_list["test3"] = 3;
    master_list["test4"] = 4;

    std::sort(custom_list.begin(), custom_list.end());
    std::set_intersection(custom_list.begin(), custom_list.end(), master_list.begin(),
                      master_list.end(), back_inserter(target_list), mycomparer());

    for(const auto & c : target_list){ cout << c << '\t' << master_list[c] << endl; }
    return 0;
}
