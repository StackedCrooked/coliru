#include <iostream>
#include <thread>
#include <mutex>
 
 class cTest
 {
     private:
     std::once_flag flag;
     
     public:
     void start(std::function<void()> init)
     {
         std::call_once(flag, [&](){ init(); });
     }  
 };
 
int main()
{
    cTest Test;
    
    for(auto i = 0; i < 5; i++)
    {
        Test.start([&](){ std::cout << "lel" << std::endl; });
        std::cout << i << std::endl;
    }
        
    return 0;
}