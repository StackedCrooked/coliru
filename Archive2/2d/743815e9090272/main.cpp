#include <memory>
#include <iostream>
using namespace std;

template<typename T>
using unique_ptr_poly = unique_ptr<T, void(*)(void*)>;

int main()
{
    cout << sizeof(unique_ptr<int>) << endl;
    cout << sizeof(unique_ptr_poly<int>) << endl;
    
    auto deleter = [](void*){}; // fake
    cout << sizeof(unique_ptr<int, decltype(deleter)>) << endl;
}
