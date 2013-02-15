#include <cassert>
#include <iostream>

enum class Color {
    Begin,
    Red = Begin,
    Orange,
    Yellow,
    Green,
    Blue,
    Indigo,
    Violet,
    End
};

struct Colors{};
Color begin(Colors) { return Color::Begin; }
Color end  (Colors) { return Color::End; }
Color operator*(Color c) { return c; }


Color operator++(Color & c)
{
    assert(c < Color::End);
    return c = static_cast<Color>(static_cast<int>(c) + 1);
}

std::ostream& operator<<(std::ostream& os, Color c)
{
    switch (c)
    {
        case Color::Red:    return os << "Red";
        case Color::Orange: return os << "Orange";
        case Color::Yellow: return os << "Yellow";
        case Color::Green:  return os << "Green";
        case Color::Blue:   return os << "Blue";
        case Color::Indigo: return os << "Indigo";
        case Color::Violet: return os << "Violet";
        default:            return os << "(Invalid Color)";
    }
}

int main()
{
    for (auto i : Colors{})
    {
        std::cout << i << std::endl;
    }
}