#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
 
int main()
{
    const std::string s[] = {"string", "1", "test", "..."};
    std::string* p = std::get_temporary_buffer<std::string>(4).first;
 
    std::copy(std::begin(s), std::end(s),
              std::raw_storage_iterator<std::string*, std::string>(p));
 
    for (std::string* i = p; i != p+4; ++i) {
        std::cout << *i << '\n';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);
}