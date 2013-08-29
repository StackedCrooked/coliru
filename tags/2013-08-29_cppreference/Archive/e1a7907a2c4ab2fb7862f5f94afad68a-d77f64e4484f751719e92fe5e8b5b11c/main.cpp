#include <cctype>

typedef int(*PF)(int);

int foo(int) {}

int main()
{
    PF p1 = &foo;
    PF p2 = &std::tolower;
}
