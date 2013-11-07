#include <iostream>
#include <array>

template <class blabla>
struct NewClassName
{
    // ...
};

template <class blabla> using OldClassName __attribute__ ((deprecated))
    = NewClassName<blabla>;

int main()
{
    OldClassName<int> a;

}