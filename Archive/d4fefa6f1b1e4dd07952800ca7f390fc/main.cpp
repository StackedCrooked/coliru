#include <iostream>
#include <utility>
#include <type_traits>

template<typename Enum> Enum
constexpr end(Enum) { return Enum(); }

template<typename Enum>
Enum& operator++(Enum & enumerator)
{
    return enumerator = next(enumerator);
}

template<typename Enum>
constexpr Enum operator+(Enum enumerator, unsigned n)
{
    return n == 0 ? enumerator : next(enumerator) + (n - 1);
}

enum class RGB
{
    Red = 1, Green = 2, Blue = 3
};

constexpr RGB begin(RGB) { return RGB::Red; }

template<typename Enum>
constexpr Enum end() { return RGB{}; }

constexpr RGB next(RGB color)
{
    return color == RGB::Red   ? RGB::Green :
           color == RGB::Green ? RGB::Blue  :
           color == RGB::Blue  ? RGB()      :
           RGB();
}


constexpr const char * to_string(RGB color)
{
    return color == RGB::Red   ? "RGB::Red"   :
           color == RGB::Green ? "RGB::Green" :
           color == RGB::Blue  ? "RGB::Blue"  : " RGB::?";
}
    

std::ostream& operator<<(std::ostream & os, RGB rgb)
{
    return os << to_string(rgb);
}

int main()
{
    for (auto i = begin(RGB{}), e = RGB{}; i != e; ++i)
    {
        std::cout << i << std::endl;
    }
}