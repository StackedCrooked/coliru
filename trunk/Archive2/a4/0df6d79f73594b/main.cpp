#include <thread>

bool b = false;
    
int main()
{    
    std::thread([&]{ b = true; }).detach();    
    
    while (!b)
    {
        std::this_thread::yield();
    }
}
