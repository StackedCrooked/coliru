#include <iostream>

struct F
{
    int x;
    int* y = &x;
    int* get_int() { return &x; }
    int** get_ptr() { return &y; }
};

void c_call(int ** x)   
{ }

int main(void)
{ 
    F f{};
    
    c_call(f.get_ptr());
}
