#include <iostream>

class test
{
public:
    const static int try1 = 1 ;
    const static int try2 ;
};

const int test::try2 = 2 ;

int main()
{
    std::cout << test::try1 << " " << test::try2 ;
}