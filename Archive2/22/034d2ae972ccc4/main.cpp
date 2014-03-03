#include <iostream>
#include <thread>
#include <functional>
 
struct X { X(){}  X(X&&){}  X(X const&) = delete; };
 
void f(X)
{
    std::cout << "hello world\n";
}
 

int main()
{
    X x;
    std::thread t(f, std::move(x));
    t.join();
}