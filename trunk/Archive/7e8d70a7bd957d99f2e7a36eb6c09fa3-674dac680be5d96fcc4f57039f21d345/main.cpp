#include <iostream>
#include <thread>
#include <unistd.h>
 
void foo()
{
    sleep(1);
}
 
int main()
{
    std::thread t;
    std::cout << "before starting, joinable: " << t.joinable() << '\n';
 
    t = std::thread(foo);
    std::cout << "after starting, joinable: " << t.joinable() << '\n';

}