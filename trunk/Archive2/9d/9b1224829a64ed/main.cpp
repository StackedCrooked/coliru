#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

template<typename T>
void foo(initializer_list<T> l)
{
    static_assert(l.size() == 3, "goo");
}

int main(int argc, char *argv[])
{
   foo({1,2,3});    
}