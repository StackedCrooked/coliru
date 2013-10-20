#include <fstream>
#include <iostream>
#include <iterator>

void readfile(const char *inputfile) {
    std::ifstream is(inputfile);
    std::string buf(std::istreambuf_iterator<char>(is), {});
    std::cout << buf << std::endl;
}

int main()
{
    readfile("main.cpp");
}
