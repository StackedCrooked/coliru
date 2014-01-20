#include <iostream>

enum class Types
{
    Wood,
    Stone,
    Iron
};

enum Meta
{
    Breakable = 1,
    Smeltable = 2
};

int typeMeta[3 /*number of types*/] = {
    Breakable,
    0,
    Breakable | Smeltable
};
    
int main (int argc, char *argv [])
{
    return 0; 
}