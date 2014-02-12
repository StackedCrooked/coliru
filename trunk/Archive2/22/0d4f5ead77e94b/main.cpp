#include <iostream>

template <typename Type>
unsigned long get_len(Type in)
{
   unsigned long i = 0;
   while (in[i]) ++i;
   return i;
}

int main()
{
    const char* c = "Hello";
    get_len(c);
}
