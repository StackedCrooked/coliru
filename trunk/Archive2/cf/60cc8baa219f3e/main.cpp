#include <iostream>

struct Z
{
    int value;
    
    Z(int value) : value(value)
    {
    }
};

int i = 0;

Z operator+(Z a, Z b)
{
    return a.value + b.value;
}

Z operator-(Z a, Z b)
{
    return a.value - b.value;
}

Z operator*(Z a, Z b)
{
    return a.value * b.value;
}

Z operator/(Z a, Z b)
{
    return a.value / b.value;
}

int shit(Z z, Z (*f)(Z, Z))
{
    try
    {
        switch (i++)
        {
            case 0: throw 1;
            case 1: throw operator+;
            case 2: throw 2;
            case 3: throw operator*;
            case 4: throw 100;
            case 5: throw operator/;
            case 6: throw 6;
            case 7: throw operator-;
            case 8: throw 8;
        }
    }
    catch (int value)
    {
        return shit(f(z, Z(value)), f);
    }
    catch (Z (*g)(Z, Z))
    {
        return shit(z, g);
    }
    return z.value;
}

int main()
{
    std::cout << shit(Z(0), [](Z a, Z b){ return b; });
}
