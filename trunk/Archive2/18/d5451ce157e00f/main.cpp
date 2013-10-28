#include <thread>
#include <iostream>
#include <functional>

void f_display(int a)
{
    std::cout << "in f_display(), with arg " << a << std::endl;
}

int main()
{
    std::function<void(int)> func = f_display;
    std::thread t(func, 5);
    t.join();
}