#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <map>

using namespace std;

int main()
{
    map<string, unsigned long> stats;
    stats["test"] += 10;
    std::cout << "test: " << stats["test"] << std::endl;
    std::cout << "test2: " << stats["test2"] << std::endl;
}
