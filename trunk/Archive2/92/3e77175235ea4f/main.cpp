#include <iostream>

struct Thing
{
    int x,y,z,a,b,c;
    float f;
    std::string s[2];
};

const Thing _gThing
{
    .x = 5, .y = 10, .z = 15,
    .s = { "hello", "world" },
};

int main(void)
{ }
