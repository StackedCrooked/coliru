#include <iostream>
#include <utility>
#include <string>


template<typename T, typename U>
constexpr int foo(std::pair<T, U> p)
{
    return p.first < 10 ? foo(std::make_pair(p.first+1, p.second+2)) : p.first + p.second;
}


constexpr std::size_t get_size(const char * c, int limit)
{
    return !limit ? 0 : !*c ? 0 : 1 + get_size(c + 1, limit -1);
}


int main()
{     
    enum {
        abc = get_size("abc", 100),
        
    };
    auto abcdef = get_size(std::string("abcdef").c_str(), 100);
    std::cout << abc << ", " << abcdef << std::endl;
}