#include <iostream>
extern int A;
static int A = 101;
class A{};
int main()
{
    std::cout << A << '\n';
}
