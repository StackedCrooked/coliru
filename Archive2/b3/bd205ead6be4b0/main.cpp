#include <iostream>

class Object {};

template <typename CharT>
inline std::basic_ostream<CharT> & operator<<(std::basic_ostream<CharT> & out, const Object&)
{
    return (out << "object");
}

class Print
{
public:
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
