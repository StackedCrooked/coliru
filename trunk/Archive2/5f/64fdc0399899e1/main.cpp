#include <thread>
#include <iostream>
#include <functional>

void f_display()
{
    std::cout << "in f_display()" << std::endl;
}

int main()
{
    std::function<void()> func = f_display;
    std::thread t(func);
    t.join();
}