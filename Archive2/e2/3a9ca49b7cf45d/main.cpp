#include <iostream>

template <typename... Args>
void foo ( Args&& ... args ) {
     for... ( decltype(auto) arg : args ) {
         // Do something with args?
     }
}

int main(){}