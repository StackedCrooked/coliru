#include <iostream>
#include <chrono>
#include "time.h"

int main()
{ 
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now(); 
    time_t time = std::chrono::system_clock::to_time_t(tp); 
    struct tm tm; localtime_r(&time, &tm); 
    strptime("10:30", "%H:%M", &tm); 
    std::cout << asctime(&tm) << std::endl;
}