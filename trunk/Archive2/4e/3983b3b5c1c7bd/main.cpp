#include <iostream>
#include <string>
#include <vector>

auto f () {
    struct { int x, y; } object;
    object.x = 0;
    object.y = 0;
    return object;
}

int main()
{
    f();
}
