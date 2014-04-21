#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    
    std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout<<"RUN TIME IS :"<<std::endl;
    std::cout << std::chrono:: duration_cast <std::chrono:: nanoseconds>(end-begin).count() << "ns" << std::endl;
    //system("PAUSE");
    //**********************************************************
    return 0;
}