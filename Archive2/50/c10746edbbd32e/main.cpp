#include <iostream>
#include <array>

struct vec2d : std::array<float, 2>
{
    vec2d(float a, float b)
    : std::array<float, 2>{{a, b}} {}
};

int main()
{
    vec2d z = {1, 2};
    std::cout << z[0] << ' ' << z[1] << '\n';
}
