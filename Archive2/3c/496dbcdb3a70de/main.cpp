#include <sstream>
#include <string>
#include <thread>
#include <iostream>

void reader (std::istream* in, std::string& out)
{
    (*in) >> out;
}

int main()
{
    std::function<void(std::istream*, std::string&)> r = reader;
    std::istringstream ss("lol");
    std::string out;
    
    std::thread t(reader, &ss, std::ref(out));
    t.join();
    std::cout << out << '\n';
}