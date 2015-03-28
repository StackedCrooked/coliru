#include <iostream>
#include <thread>
#include <functional>
 
struct X { X(){}  X(X&&){}  X(X const&) = delete; };
 
template <class T>
void f(T &&) {}
 
template <class T>
std::thread * doThread(T && t) {
    return new std::thread(f<T>, std::forward<T>(t));
}
 

int main()
{
    std::thread * t = doThread(X());
    t->join();
    delete t;

    X x;
    t = doThread(x);
    t->join();
    delete t;
}