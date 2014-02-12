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
    while(b) {a = inc(a); b = dec(b);}
    return a;
}

Natural mul(Natural a, Natural b)
{
    Natural c = zero;
    while (a) {c = add(b, c); a = dec(a);}
    return c;
}

void len(Natural a)
{
    do std::cout << '.'; while ((a = dec(a)));
}
