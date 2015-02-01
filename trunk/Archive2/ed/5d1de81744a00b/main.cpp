#include <vector>
#include <iostream>
#include <functional>
#include <boost/variant.hpp>

int main () {
    int captured = 42;
    auto l0 = [&captured](int x){ captured += x; }; 
    auto l1 = [&captured](int x){ captured -= x; };
    auto l2 = [&captured](int x){ captured = x + 1; };
    
    std::vector<boost::variant< decltype(l0), decltype(l1), decltype(l2)>> variant;
    variant.push_back(l0);
    variant.push_back(l1);
    variant.push_back(l2);
    
    auto f =  boost::get<decltype(l1)>(variant[1]);

    int i = 1;
    f(i);
    std::cout << captured;
}