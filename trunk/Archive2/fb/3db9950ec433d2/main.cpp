#include <iostream>
#include <iomanip>
#include <string>

enum class Stuff
{
    A,
    B,
    C
};

template<Stuff S>
struct Thing
{
    static bool gimme() { return true; }
};

template<>
struct Thing<Stuff::A>
{
    static float gimme() { return 1.23f; }
};

template<>
struct Thing<Stuff::B>
{
    static std::string gimme() { return ":D"; }
};

int main()
{
    std::cout << std::boolalpha << Thing<Stuff::A>::gimme() << "\n" << Thing<Stuff::B>::gimme() << "\n" << Thing<Stuff::C>::gimme() << "\n";
    
}
