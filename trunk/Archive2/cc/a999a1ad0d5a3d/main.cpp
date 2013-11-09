#include <initializer_list>
#include <iostream>

struct string
{
    string() = default;
    string& operator=(string const&)
    {
        std::cout << "copy-assignment\n";
        return *this;
    }
    string& operator=(char)
    {
        std::cout << "assignment from a char\n";
        return *this;
    }
    string& operator=(char const*)
    {
        std::cout << "assignment from a char const*\n";
        return *this;
    }
    // enable me to resolve the ambiguity *magic*
    /*string& operator=(std::initializer_list<char>)
    {
        std::cout << "assignment from an initializer_list<char>\n";
        return *this;
    }*/
};

int main()
{
    string str;
    str = {};
}