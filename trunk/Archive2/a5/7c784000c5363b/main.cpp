#include <iostream>
#include <thread>
auto id = std::this_thread::get_id();
thread_local auto id3 = std::this_thread::get_id();
int main()
{

    auto id2 = std::this_thread::get_id();
    
    std::cout << id << std::endl << id2 << std::endl << id3 << std::endl;
}