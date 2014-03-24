#include <iostream>

const char *p[] = { "abc", "efg" };

int main(int argc = 2, const char **argv = p)
{
    std::cout << argc << std::endl;
}
