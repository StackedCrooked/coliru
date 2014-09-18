#include <array>
#include <time.h>
#include <iostream>
int main()
{
time_t t1 = time(0);
for (int i= 0; i<10000; i++)
{
    
    std::array<char, 5000000> a;
    
    a[1] = 'c';
}
time_t t2 = time(0);
for (int i= 0; i<10000; i++)
{
    
    std::array<char, 5000000> a{};
    a[1] = 'c';
}
time_t t3 = time(0);

std::cout << t2-t1 << "\n" << t3-t2;
}   
