
#include <iostream>
namespace N
{
    extern int i;
    int j = 6;
}
int j = 5;
int N::i = j;
int main (void)
{
    std::cout << N::i << std::endl;
}
