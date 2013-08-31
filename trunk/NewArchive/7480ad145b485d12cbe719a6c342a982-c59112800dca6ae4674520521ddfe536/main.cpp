#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <vector>

void locked_print(const std::string& s)
{
    static std::mutex _mutex ; 
    _mutex.lock(); 
    std::cout << s ;
    _mutex.unlock();
}

void print(const std::string& s, int n)
{
    for(auto i=0; i<n; ++i)
        locked_print(s); 
    locked_print("\n"); 
}

int main()
{
    constexpr int num = 4 ;
    std::vector<std::thread> threads ;
    for(auto i=num; i>0; --i)
        threads.push_back(std::thread(print, "123", i));
    for(auto j=num-1; j>=0; --j)
        threads[j].join(); 
    return 0;
}
        