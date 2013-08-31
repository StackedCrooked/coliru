#include <cstdint>
#include <cstring>

float InverseSquare_cast(float x)
{
    static_assert(sizeof(float) == sizeof(std::int32_t), "BOOM!");
    float xhalf = 0.5f*x;
    std::int32_t i = reinterpret_cast<int32_t&>(x);
    i = 0x5f3759df - (i>>1);
    x = reinterpret_cast<float&>(i);
    x = x*(1.5f - xhalf*x*x);
    return x;
}

float InverseSquare_memcpy(float x)
{
    static_assert(sizeof(float) == sizeof(std::int32_t), "BOOM!");
    float xhalf = 0.5f*x;
    std::int32_t i;
    std::memcpy(&i, &x, sizeof(i));
    i = 0x5f3759df - (i>>1);
    std::memcpy(&x, &i, sizeof(i));
    x = x*(1.5f - xhalf*x*x);
    return x;
}
