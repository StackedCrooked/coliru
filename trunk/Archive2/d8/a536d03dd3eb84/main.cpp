#include <iostream>
#include <string>
#include <tuple>

#define P_(x) \
    std::cout << __FUNCTION__ << ':' << __LINE__ << "  " \
              << #x << " == " << (x) << std::endl

int main() {
    std::tuple<std::string, int> t1("abc", 42);
    auto t2 = std::make_tuple(12.5, "def", 0);
    
    P_(std::get<0>(t1));
    P_(std::get<1>(t1));
    std::get<1>(t1) = -1;
    P_(std::get<1>(t1));
    
    P_(std::get<0>(t2));
    P_(std::get<1>(t2));
    P_(std::get<2>(t2));
    
    int x;
    std::string s;
    
    std::tie(s, x) = t1;
    
    P_(s);
    P_(x);

    std::tie(std::ignore, s, x) = t2;
    
    P_(s);
    P_(x);

}
