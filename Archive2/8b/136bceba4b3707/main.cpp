#include <iostream>
#include <thread>
     
void f(char const * p)
{
    std::cout << p << std::endl;
}
     
     
int main()
{
    std::thread t(f, "foo");
    t.join();
}