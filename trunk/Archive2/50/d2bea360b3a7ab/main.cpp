#include <iostream>
#include <cstdint>

template<typename X,typename Y,typename Z >
void checkParameter( X val, Y lower, Z upper)
{
    std::cout << val << ", " << lower << ", " << upper << "\n";
    if( ( val > upper) || ( val < lower) )
    {
        std::cout << "fail\n";
    }else
    {
        std::cout << "pass\n";
    }
}

int main()
{
    int64_t var = 8070450530100445183;
    checkParameter( var, 0LL, 8070450530100445183LL);
}