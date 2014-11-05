#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <map>

template<typename T>
void dtc(const std::map<char, T>& map)
{
    for (auto kv : map) {
        delete kv.second;
    }
}

template<typename T>
void show(std::map<char, T>& m)
{
    for (auto kv : m) {
        std::cout<< kv.first <<": " << *kv.second << std::endl;
    }
    m.erase(m.begin(), m.end());
}
 
int main()
{
    std::map<char, int*> mi;
    mi['a'] = new int(4);
    mi['b'] = new int(2);
    show(mi);
    dtc(mi);
    show(mi);
}