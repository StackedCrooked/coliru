#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <map>

int main()
{
    std::map<std::string, std::atomic_ullong> stats;
    stats["test"] += 10;
    std::cout << "test: " << stats["test"] << std::endl;
    std::cout << "test2: " << stats["test2"] << std::endl;
}
