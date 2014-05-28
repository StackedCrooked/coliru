#include <vector>
#include <map>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <string>
#include <iterator>
#include <iostream>
using namespace std;
using boost::adaptors::map_keys;

struct SomeCustomId { 
    int id;
    operator int() const { return id; }
    SomeCustomId() : id(0) {}
    SomeCustomId(int c)  : id(c) { }
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

    boost::sort(custom_list);
    boost::set_intersection(custom_list, master_list | map_keys, back_inserter(target_list));

    for(const auto & c : target_list){ cout << c << '\t' << master_list[c] << endl; }
    return 0;
}
