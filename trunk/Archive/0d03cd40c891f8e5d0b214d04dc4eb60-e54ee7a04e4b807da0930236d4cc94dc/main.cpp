#include <iostream>
#include <string>

std::string basename(const std::string& path)
{
    return path.substr(path.rfind('/') + 1);
}

int main()
{
    std::cout << basename("test") << std::endl;
    std::cout << basename("./test") << std::endl;
    std::cout << basename("./bin/test") << std::endl;
    std::cout << basename("/bin/test") << std::endl;
}