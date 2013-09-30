#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
 
int main()
{
    std::string* p;
    std::size_t sz;
    std::tie(p, sz)  = std::get_temporary_buffer<std::string>(4);
    std::uninitialized_fill_n(p, sz, "Example");
 
    for (std::string* i = p; i != p+sz; ++i) {
        std::cout << *i << '\n';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);
}