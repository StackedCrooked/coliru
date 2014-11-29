#include <iostream>
#include <initializer_list>

using namespace std;

auto a = {1, 2};

std::initializer_list<int> init_list = {1, 3, 6, 7};

decltype(a) b = init_list;

int main()
{ 
    std::cout << 3[init_list.begin()] << std::endl;
}