#include <fstream>
#include <iterator>

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    return in? std::string(std::istreambuf_iterator<char>(in), {}) : throw(errno);
}

int main()
{
    return get_file_contents("main.cpp").length();
}
