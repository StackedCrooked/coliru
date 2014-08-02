#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::cout << "BEGIN" << std::endl;
    std::ifstream f("/etc/passw");
    std::string s;
    f >> s;
    std::cout << s << std::endl;
    std::cout << "END" << std::endl;
}
