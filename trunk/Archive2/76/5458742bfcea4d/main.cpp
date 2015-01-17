#include <iostream>

class Object {};

class Print
{
public:
    inline friend std::basic_ostream<char> & operator<<(std::basic_ostream<char> & out, const Object&)
    {
        return (out << "object");
    }
    static void f( const Object& str )
    {
        std::cout << str;
    }
};


int main()
{
    std::cout << Object() << std::endl;

    return 0;
}
