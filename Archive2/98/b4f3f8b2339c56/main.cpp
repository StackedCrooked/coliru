#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <map>

int main()
{
    std::map<std::string, std::atomic_ullong> stats;
    std::cout << "test: " << stats["test"] << std::endl;
}
