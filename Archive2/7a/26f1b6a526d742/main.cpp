#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <memory>

enum class Color : unsigned
{
    WHITE = 0XFFFFFFFF,
    BLACK = 0X00000000,
    TRANSPARENT = 0XFFFFFF00,
    BLUE = 0X0000FFFF,
    CYAN = 0X00FFFFFF,
    GREEN = 0X008000FF,
    MAGENTA = 0XFF00FFFF,
    ORANGE = 0XFFA500FF,
    PINK = 0XFFC0CBFF,
    RED = 0XFF0000FF,
    YELLOW = 0XFFFF00FF,
    GRAY = 0XA9A9A9FF,
    DARK_GRAY = 0X808080FF,
    LIGHT_GRAY = 0XD3D3D3FF,
    LIME = 0X00FF00,
    SILVER = 0XC0C0C0,
    MAROON = 0X800000,
    OLIVE = 0X808000,
    PURPLE = 0X800080,
    TEAL = 0X008080,
    NAVY = 0X000080,
};

class CColor
{
public:
    explicit CColor(Color color) {}
};

int main()
{
    CColor my_color{Color::BLUE};
}