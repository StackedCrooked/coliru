#include <string>
#include <iostream>
#include <memory>

struct O
{
    ~O()
    {
        std::cout << "~O()\n";
    }
};

struct wrapper
{
    O const& val;
};
 
struct wrapper2
{
    std::string val;
};
 
int main()
{
    std::cout << "case 1-----------\n";
    {
        auto&& a = wrapper{O()};
        std::cout << "end-scope\n";
    }
    std::cout << "case 2-----------\n";
    {
        auto a{new wrapper{O()}};
        std::cout << "end-scope\n";
    }
    return 0;
}