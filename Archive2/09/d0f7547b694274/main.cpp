#include <fstream>
#include <utility>
#include <string>
int main()
{
    std::ofstream f0;
    std::ofstream f1("test.bin", std::ios::binary);
    std::string name = "example.txt";
    std::ofstream f2(name);
    std::ofstream f3(std::move(f1));
}