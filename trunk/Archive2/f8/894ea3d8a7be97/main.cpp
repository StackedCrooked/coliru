#include <fstream>
#include <utility>
#include <string>
int main()
{
    std::ifstream f0;
    std::ifstream f1("test.bin", std::ios::binary);
    std::string name = "example.txt";
    std::ifstream f2(name);
    std::ifstream f3(std::move(f1));
}