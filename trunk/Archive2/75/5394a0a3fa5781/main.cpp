#include <iostream>
#include <array>

struct vec3
{
    float x, y, z;
};

int main()
{   
    std::array<vec3, 4> xs {{
        vec3{ 0.f, 1, 2 },
        vec3{ 3.f, 4, 5 },
        vec3{ 5.f, 6, 7 },
        vec3{ 0.f, 5, 1 }
    }};
    float* xp = &(xs[0].x);
    for (size_t i = 0; i < xs.size() * 3; ++i)
    {
        std::cout << xp[i] << std::endl;
    }
}
