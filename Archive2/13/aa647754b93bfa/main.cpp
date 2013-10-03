#include <fstream>
#include <utility>
#include <string>
int main()
{
std::fstream f0;
    std::fstream f1("test.bin", std::ios::binary);
    std::string name = "example.txt";
    std::fstream f2(name);
    //std::fstream f3(std::move(f1));
}