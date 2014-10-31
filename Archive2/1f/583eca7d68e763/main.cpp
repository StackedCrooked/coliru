#include <stdexcept>
void F1();
void F2();

int main(int argc, char* argv[])
{
    F1();
    getchar();
    return 0;
}

void F1()
{
    throw std::logic_error("doh"); // Unconditional Throw.  F2() should never be executed!
    F2();
}

void F2()
{
    printf("Reached the bottom of the callstack\n"); // But this message still happens!
}
