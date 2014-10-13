#include <iostream>
#include <thread>
#include <utility>


template<typename T> T make(){ T t;return t;}

int * const *p1 = make<int const **>(); 

int main()
{


}
