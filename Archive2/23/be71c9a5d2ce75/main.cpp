#include <iostream>
#include <thread>
#include <chrono>


int main()
{
    int ints[] = {1,2,3,4,5};
    for (auto x : ints) {
        std::cout << x << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "time: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
    }
}