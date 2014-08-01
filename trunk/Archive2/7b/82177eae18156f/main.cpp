#include <iostream>
#include <functional>
using namespace std; // LOOK HERE

template<typename T>
struct function {};

template<typename T>
struct function1D : public function<T> {};


int main()
{
    function1D<int> fnInt;
    std::cout << "OK\n";
}