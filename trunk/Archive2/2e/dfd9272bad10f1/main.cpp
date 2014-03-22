#include <future>
#include <iostream>
#include <map>
#include <thread>
#include <string.h>

std::map<std::thread::id, int> indexes;

int main()
{
    auto a = std::async(std::launch::async, [=]{ return indexes[std::this_thread::get_id()]++; });
    auto b = std::async(std::launch::async, [=]{ return indexes[std::this_thread::get_id()]++; });
    auto c = std::async(std::launch::async, [=]{ return indexes[std::this_thread::get_id()]++; });
    std::cout << a.get()  << ' ' << b.get() << ' ' << c.get() << std::endl;
}