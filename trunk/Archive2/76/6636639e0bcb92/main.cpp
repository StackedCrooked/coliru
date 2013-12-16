#include <fstream>

std::ofstream func() {
    std::ofstream file("file.txt");
    return file;
}

int main()
{
    std::ofstream file = func();
}
