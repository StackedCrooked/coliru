#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
void f(T v)
{
    cout << __PRETTY_FUNCTION__ << endl;
    //typename remove_reference<T>::type x = v; // copy of v
    auto x = v;
    T y = v; // maybe copy of v; maybe a reference to x
    ++x; //increment local variable
    ++y;
}

int main()
{
   f(10);
   int i = 0;
   f(i);
   cout << i << endl;
}
