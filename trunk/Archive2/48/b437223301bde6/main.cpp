#include <array>

enum E
{
    VAL_A = 1,
    VAL_B = 1
};

int main()
{
    const std::array<const int, VAL_B> arr = { 1 };
    
    return 0;
}