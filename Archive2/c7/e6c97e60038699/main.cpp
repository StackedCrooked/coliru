#include <iostream>
#include <string>

struct Foo { std::string a; int b; float c; };

int main()
{
    Foo arr[2] = { { "bar", 0, 0.0f }, { "baz", 1, 2.0f } };
    
    std::cout << arr[0].b << " " << arr[1].c << std::endl;
    return 0;
}