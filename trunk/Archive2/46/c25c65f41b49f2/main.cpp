#include <iostream>

enum lewd{PLUS, MINUS};

struct lawd
{
    int a;
    int& operator()(lewd lw, int value)
    {
        if(lw == PLUS)
        {
            a+=value;
        }
        
        return a ; // *** added
    }
};

int main()
{
    lawd lel;
    lel.a = 1;
    lel(PLUS, 2);
    std::cout << lel.a << '\n' ;
}