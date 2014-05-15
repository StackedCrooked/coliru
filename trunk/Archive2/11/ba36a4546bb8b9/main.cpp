#include <iostream>

struct runtime_entry_point
{
    friend int main();
};

int main()
{
    std::cout << "Hello, world!" << std::endl;
}
