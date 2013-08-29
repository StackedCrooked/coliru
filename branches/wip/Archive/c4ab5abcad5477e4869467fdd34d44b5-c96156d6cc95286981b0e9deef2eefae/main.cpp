#include <iostream>

struct Test
{
    int* begin() { return &data[0]; }
    int* end()   { return &data[2]; }
    int data[2];
};

int main()
{
        Test arr { 1, 2 };
        for(auto i: arr)
            std::cout << i << "\n";
}