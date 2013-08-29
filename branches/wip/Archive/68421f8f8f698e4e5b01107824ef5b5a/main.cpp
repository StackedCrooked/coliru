#include <iostream>
#include <thread>

int main()
{
    printf("%.2f\n",1234.4567);
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
}