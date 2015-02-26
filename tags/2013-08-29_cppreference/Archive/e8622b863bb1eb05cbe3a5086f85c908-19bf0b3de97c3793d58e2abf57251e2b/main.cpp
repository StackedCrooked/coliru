#include <array>
#include <iostream>
#include <thread>


int Id;
const int Max = 2000000;


int main(int argc, char**)
{
    // let's race :)    
    auto loop = [argc]{ for (auto i = 0UL; i != Max/argc; ++i) { ++Id; } };
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