#include <iostream>
#include <string>
#include <fstream>

std::ofstream func() {
    std::cout << "hi";
    std::ofstream file("file.txt");
    return file;
}

int main()
{
    std::ofstream file = func();
}
