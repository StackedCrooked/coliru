#include <map>
#include <iostream>
#include <cstring>

struct my_sz_cmp
{
    bool operator()(const char* a, const char* b) const
    {
        if (!(a && b))
            return a < b;
        else
            return strcmp(a, b) < 0;
    }
};

int main()
{
    std::map<char const*, int, my_sz_cmp> map;

    map.insert(std::make_pair("one",   1));
    map.insert(std::make_pair("two",   2));
    map.insert(std::make_pair("three", 3));
    map.insert(std::make_pair("four",  4));

    char uniq_three[] = "three";
    std::cout << std::boolalpha << uniq_three << " -> " << map[uniq_three] << '\n';
}
