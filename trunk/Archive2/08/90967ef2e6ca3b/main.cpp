#include <iostream>

struct DynamicArray
{
};

DynamicArray& operator<<( DynamicArray& da, int i )
{
    std::cout << "<<" << i << std::endl;
    return da;
}

DynamicArray& operator,( DynamicArray& da, int i )
{
    std::cout << "," << i << std::endl;
    return da;
}

int main()
{
    DynamicArray da;
    da << 1, 2, 3,
          4, 5, 6,
          7, 8, 9;
}
