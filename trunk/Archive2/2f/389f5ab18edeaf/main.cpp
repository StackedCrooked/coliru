#include <iostream>

#define DCHECK(x)  if (!(x)) { std::cout << "Oops\n"; }

int main()
{
    DCHECK(([]{ return false; }()));
}
