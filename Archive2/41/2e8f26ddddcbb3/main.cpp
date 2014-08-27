#include <array>

enum E
{
    VAL_A = 1,
    VAL_B = 1
};

int main()
{
    E e = VAL_A;
    switch(e)
    {
        case VAL_A:
            return VAL_A;
            break;
        case VAL_B:
            return VAL_B;
            break;
        default:
            return 0;
            break;
    };
    
    const std::array<const int, VAL_B> arr = { 1 };
    
    return 0;
}