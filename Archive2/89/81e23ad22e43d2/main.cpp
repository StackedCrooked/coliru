#include <thread>
#include <iostream>
#include <functional>

void f_display(int a)
{
    std::cout << "in f_display(), with arg " << a << std::endl;
}

int main()
{
    std::thread t([](int x){f_display(x);}, 5);
    t.join();
}