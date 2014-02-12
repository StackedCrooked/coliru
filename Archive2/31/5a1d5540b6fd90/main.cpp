#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

 
void foo()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    time_t t = time(0);
    struct tm * now = localtime(&t);
    std::cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << ' '
         << now->tm_hour << ':'
         << now->tm_min << ':'
         << now->tm_sec 
         << std::endl;    
}
 
void bar()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(3));
        time_t t = time(0);
    struct tm * now = localtime(&t);
    std::cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << ' '
         << now->tm_hour << ':'
         << now->tm_min << ':'
         << now->tm_sec 
         << std::endl;  
}
 
int main()
{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    std::cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << ' '
         << now->tm_hour << ':'
         << now->tm_min << ':'
         << now->tm_sec 
         << std::endl;

    std::cout << "starting first helper...\n";
    std::thread helper1(foo);
 
    std::cout << "starting second helper...\n";
    std::thread helper2(bar);
 
    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();
 
    std::cout << "done!\n";
}