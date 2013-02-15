#include <iostream>

void real_foo(unsigned count, unsigned...) {
    va_list ap;
    va_start(ap, count); //Requires the last fixed parameter (to get the address)
    for(j=0; j<count; j++)
        std::cout << va_arg(ap, unsigned); //Requires the type to cast to. Increments ap to the next argument.
    va_end(ap);
}

template<class ...Ts>
void auto foo(Ts... Vs)
{
    foo(sizeof(Ts), (unsigned)Vs...);
}

int main() {
   foo(3, 5u, 6.123);
}