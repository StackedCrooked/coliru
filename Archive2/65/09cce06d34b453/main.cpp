#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
 
int main()
{
    std::vector<std::string> v = {"This", "is", "an", "example"};
 
    std::string* p;
    std::size_t sz;
    std::tie(p, sz)  = std::get_temporary_buffer<std::string>(v.size());
    sz = std::min(sz, v.size());
 
    std::uninitialized_copy(v.begin(), v.begin() + sz, p);
 
    for (std::string* i = p; i != p+sz; ++i) {
        std::cout << *i << ' ';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);
}