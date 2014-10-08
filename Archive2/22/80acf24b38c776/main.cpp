#include <thread>
#include <iostream>
#include <functional>

void func(int x, int& y) 
{ 
    y += x; 
} 

int main()
{
    int y(15); 
    int x(15); 
    std::thread t(func, x, std::ref(y)); 
    t.join(); 
    std::cout << y;
}