#include <iostream>
#include <string>
#include <sstream>


struct LogItem
{
    template<int N>
    void operator<<(const char (&literal)[N])
    {
        std::cout << "const char[N]";
        ss << literal;        
    }

    void operator<<(const char* str)
    {
        std::cout << "const char*\n";
        ss << str;
    }
    
    std::stringstream ss;
};


int main()
{
    LogItem item;
    item << "literal";
}
