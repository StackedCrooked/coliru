#include <stdio.h>

class A
{
    public:

    //  If I make g() as virtual, stdio doesn't print.
    virtual void g() {}
};

int main()
{
    A a; // Or I could remove this object to make stdio print.
    printf("testing\n");
}