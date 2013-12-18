#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <limits>

class Item {
    public:
    Item() {}
    Item(const Item&) { std::cout << "Copy" << std::endl; }
    Item(Item&&) { std::cout << "Move" << std::endl; }   
};

class Items {
    public:
    Item _v;
    Items(Item v) : _v(std::move(v)) { }
};

int main()
{
    Item i;
    Items is(i);
    Items is2(std::move(i));
   /* std::vector<std::size_t> t {64};
    std::cout << (1 << t[0]) << std::endl;
    std::cout << (1ull << t[0]) << std::endl;
    std::cout << (-1ull) << std::endl;
    std::cout << std::numeric_limits<unsigned long long>::max() << std::endl; */
}
