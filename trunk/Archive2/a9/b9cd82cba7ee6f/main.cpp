#include <cstdlib>

int main()
{
tryagain:   // a label, to which 'goto' can jump
    const int x = std::rand();  // look, it's const
    if(!(  (x*1000)%2 == 0   ) )
        goto tryagain;         // but I can still change it, even though it's const!
    return x;
}
