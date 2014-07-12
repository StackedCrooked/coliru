#include <memory>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include <cxxabi.h>


std::string Demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&free)>(p, &free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
    }
}


template<typename T>
std::string GetTypeName(T&&)
{
    return Demangle(typeid(T).name());
}


#include <iostream>
#include <typeinfo>


struct Color
{
    enum Red   { Red = 1 };
    enum Green { Green = 2 };
    enum Blue  { Blue = 3 };

    Color(enum Red) : value(Red)  {}
    Color(enum Green) : value(Green)  {}
    Color(enum Blue) : value(Blue)  {}

    operator int() const { return value; }

private:
    friend std::ostream& operator<<(std::ostream& os, Color c)
    {
        switch (c)
        {
            case Red: return os << GetTypeName(Red);
            case Green: return os << GetTypeName(Green);
            case Blue: return os << GetTypeName(Blue);
            default: throw 1;
        }
    }

    int value;
};


int main()
{
    Color c = Color::Red;

    std::cout << c << std::endl;


    switch (c)
    {
        case Color::Red: std::cout << "it is red" << std::endl; break;
        default: std::cout << "it is not red" << std::endl; break;
    }


}
