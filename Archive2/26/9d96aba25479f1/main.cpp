#include <iostream>
#include <array>
#include <unordered_map>
#include <functional>
#include <cstdint>

enum class T : uint8_t
{
    A = 0,
    B = 1
};

struct X
{
    T t : 1;
};

int main()
{
}