#include <array>
#include <iostream>
#include <thread>


int Id;
const int Max = 2000000;


int main(int argc, char**)
{
    std::cout << "argc: " << argc << std::endl;
    auto threadMax = Max/argc;
    // let's race :)    
    auto loop = [=]{ for (auto i = 0UL; i != threadMax; ++i) { ++Id; } };
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
    std::cout << "Difference: " << (Id - Max) <<" (" << static_cast<int>(0.5 + 100.0 * (Id - Max) / Max) << "%)" << std::endl;
}