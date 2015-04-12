#include <iostream>

class Foo
{
    
public:
    int i;
};

int main()
{
    unsigned int width = 3;
    unsigned int length = 5;
    
    Foo f_arr[3][5];
    
    //Why does this work? Because multi-dimensional arrays are actually 1D.
    for (unsigned int j = 0; j < width*length; ++j)
        f_arr[0][j].i = j;
    
    //If you notice, if the size is known, 0 * 5^1 + 4 * 5^0 = 4
    //2 * 5^1 + 4 * 5^0 = 14
    std::cout << f_arr[0][4].i << std::endl;
    std::cout << f_arr[2][4].i << std::endl;
}
