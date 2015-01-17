#include <iostream>

class Object {};

class Print
{
public:
    template <typename CharT>
    inline friend std::basic_ostream<CharT> & operator<<(std::basic_ostream<CharT> & out, const Object&)
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
