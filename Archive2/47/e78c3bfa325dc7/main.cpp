#include <iostream>
#include <chrono>
#include <thread>

int main(){
    std::chrono::steady_clock::time_point start(std::chrono::steady_clock::now());
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::chrono::steady_clock::time_point end(std::chrono::steady_clock::now());
    
    
    //std::chrono::duration<double> duration = end - start;
    //double elapsedTimeMs = duration.count();
    
    std::chrono::milliseconds ms(std::chrono::duration_cast<std::chrono::milliseconds>(end - start));
    
    std::cout << ms.count() << std::endl;
}