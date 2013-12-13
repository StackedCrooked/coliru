#include <iostream>

class X
{
    public:
        static const int x = 5;
        static constexpr int y = 6;
        static constexpr double pi = 3.1415;
};

//const int X::x; //definicja nie zawsze potrzebna, a nwet jesli potrzebna, to nie podajesz inicjalizatora

int main()
{
     std::cout << X::x << '\n' << X::y << '\n' << X::pi;
}
