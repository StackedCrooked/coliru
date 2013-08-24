#include <array>
#include <iostream>
#include <thread>


uint64_t Id;
const uint64_t Max = 10UL * 1000UL * 1000UL * 1000UL * 1000UL;


int main()
{
    // let's race :)    
    auto loop = []{ while (Id < Max) ++Id; };
    std::array<std::thread, 4> threads { 
        std::thread(loop),
        std::thread(loop),
        std::thread(loop),
        std::thread(loop)
    };
    
    for (auto& t : threads)
    {
        t.join();
    }
    
    
    std::cout << "Id=" << Id << std::endl;
    std::cout << "Max=" << Max << std::endl;
    std::cout << "Difference: " << (Id - Max) << std::endl;
}