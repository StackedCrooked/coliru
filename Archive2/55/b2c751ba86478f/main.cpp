#include <iostream>
#include <cstring>

using namespace std;

struct Foo;

extern Foo f;

int main()
{
    Foo (*c)[7];
}