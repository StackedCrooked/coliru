class foo
{
};

class bar
{
    foo f;
    int m;
};

class cat : foo
{
    int m;
};

#include <iostream>

int main()
{
    std::cout << sizeof(bar) << " " << sizeof(cat) << "\n";
}