#include <iostream>
#include <string>
#include <exception>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <thread>

class Myexcept : public std::exception
{
    const char* s{};
    int errorval{};
public:
    Myexcept() : s{}, errorval{} {}
    Myexcept(const char* str, int e) : s{str}, errorval{e} {}
    ~Myexcept(){ delete s; }
    
    void what() { std::cout << s << "at position: " << errorval << std::endl; }
};

void parse()
{
    std::string str{"MynameisJames"};
    
    for (auto i = 0; i < 100; i++)
    {
        if (std::isalpha(str.at(i)))
            std::cout << "Yay\n";
        else
            throw Myexcept{"notaletr", i};
    }
}

void print()
{
    for (int i = 0; i < 200; i++)
        std::cout << "James\n";
}

int main()
{
    try
    {
        std::thread t1(parse);
        t1.join();
    }
    catch (std::out_of_range me)
    {
        std::cout << me.what() << std::endl;
    }
    //std::thread t1(parse);
    std::thread t2(print);
    //t1.join();
    t2.join();
}


