#include<iostream>
#include<chrono>
#include<ctime>
#include<iomanip>
#include<string>

int main(){
    using namespace std::chrono;
    auto t = system_clock::to_time_t(system_clock::now());
    std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %X") << std::endl;
    std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << std::endl;
    return 0;
}
