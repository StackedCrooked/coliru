#include <iostream>

typedef void *Natural;
const Natural zero = nullptr;

Natural inc(Natural a);
Natural dec(Natural a);
Natural add(Natural a, Natural b);
Natural mul(Natural a, Natural b);
void len(Natural a);

int main()
{
    std::cout << "pointer arithmetic: 2 * (3 + 1) = ";
    len(mul(inc(inc(zero)), add(inc(inc(inc(zero))), inc(zero))));
    
    std::cout << "Fibonacci sequence: \n";
    Natural a = zero, b = inc(zero);
    while ("hope coliru times out")
    {
        len(a);
        Natural temp = a;
        a = add(a, b);
        b = temp;
    }
}



Natural inc(Natural a)
{
    return new Natural(a);
}

Natural dec(Natural a)
{
    return a ? *reinterpret_cast<Natural*>(a) : zero;
}

Natural add(Natural a, Natural b)
{
    while (a) {b = inc(b); a = dec(a);}
    return b;
}

Natural mul(Natural a, Natural b)
{
    Natural c = zero;
    while (a) {c = add(b, c); a = dec(a);}
    return c;
}

void len(Natural a)
{
    while (a) {std::cout << '.'; a = dec(a);}
    std::cout << '\n';
}
