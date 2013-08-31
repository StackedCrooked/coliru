#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <array>
#include <string>
#include <cstdint>
#include <memory>

class stuff
{
    explicit stuff(int) { std::cout<<"basecon\n"; }
    
public:
    stuff(): stuff(0) { std::cout<<"defcon\n"; }
    stuff(const stuff&): stuff(0) { std::cout<<"copycon\n"; }
};

int main()
{
    stuff s;
}