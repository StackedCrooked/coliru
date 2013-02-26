#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread1!"; });
    std::thread f([](){ std::cout << "Hello Thread2!"; });
    {
        t.join();
        f.join();
    }
    return 0;
}