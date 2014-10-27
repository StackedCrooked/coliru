#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std::literals;

int main ()
{
    std::multimap<std::string,int> mymm;

    mymm.insert(std::make_pair("Hello"s,50));
    mymm.insert(std::make_pair("Bye"s,100));
    mymm.insert(std::make_pair("Bye"s,150));
    mymm.insert(std::make_pair("Bye"s,200));
    mymm.insert(std::make_pair("?"s,250));
    mymm.insert(std::make_pair("?"s,300));

    std::vector<int> keys;
    for(auto it = mymm.cbegin(), end = mymm.cend(); it != end; it = mymm.upper_bound(it->first)) {
        std::cout << it->first << ' ' << mymm.count(it->first) << '\n';
    }
}