#include <fstream>
#include <future>
#include <iostream>
#include <sstream>
#include <cstring>


std::string read_file(const char *filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in)
    {
        std::stringstream ss;
        ss << "Failed to open file \"" << filename << "\". Reason: " << strerror(errno) << ".";
        throw std::runtime_error(ss.str());  
    }
    
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}


void test()
{
    std::cout << std::async(read_file, "bla bla bla").get() << std::endl;
}


int main()
{
    try
    {
        test();
    }
    catch (const std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
}
