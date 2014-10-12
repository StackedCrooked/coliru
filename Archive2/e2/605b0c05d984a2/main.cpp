#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main() {
    std::fstream stream("foo.txt", std::ios::app);
    stream << "Hello, World!\n";
    stream.close();
    std::system("ls -l foo.txt");

    stream.open("foo.txt", std::ios::in);
    std::cout << stream.rdbuf() << std::flush;
    stream.close();

    stream.open("foo.txt", std::ios::out | std::ios::trunc);
    std::system("ls -l foo.txt");
}
