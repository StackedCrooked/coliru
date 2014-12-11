#include <iostream>

struct F
{
    int x;
    int * get_int() { return &x; }
};

void c_call(int ** x)   
{ }

int main(void)
{ 
    F f{};
    
    c_call(&(f.get_int()));
}
