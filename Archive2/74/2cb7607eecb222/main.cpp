#include <iostream>
#include <cstring>

using namespace std;

int (*(*(*foo)(const void *)()))[3];

struct Foo{ };


int main()
{
    Foo (*c)[7];
}