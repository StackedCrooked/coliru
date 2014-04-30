#include <thread>

bool get_bool();
void set_bool(bool);
    
int main()
{    
    std::thread([&]{ set_bool(true); }).detach();    
    
    while (!get_bool())
    {
        std::this_thread::yield();
    }
}
