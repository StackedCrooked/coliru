#include <iostream>
#include <cstring>

using namespace std;

using array_type = int (*)[10];

typedef int(*)[10] array_type;
//using return_type = array_type (*)();

int (*x())[3];

struct Foo{ };


int main()
{
    Foo (*c)[7];
}