#include <iostream>
#include <type_traits>
#include <ratio>
 
int main()
{
    std::ratio<1,3> one_third;
    std::ratio<2,4> two_fourths;
    std::ratio_add<decltype(one_third), decltype(two_fourths)> sum;
    std::cout << decltype(sum)::den << std::endl;
}
