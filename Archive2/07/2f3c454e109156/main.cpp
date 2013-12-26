#include <iostream>
void print(double);  // name 'print' declared at namespace scope
void fooBar(int ival)
{
    void print(int); //  name 'print' declared at block scope
    void foo(); // name 'foo' declared at block scope (and unused)

    print(3.14); // name 'print' from the block scope is found
                 // lookup does not proceed to namespace scope
                 // this compiles a call to void print(int)
}

void foo()
{
    print(3.14);  // name 'print' is not declared at this block scope
                  // so lookup proceeds to namespace scope
                  // this compiles a call to void print(double)
    print(3);     // same.
}

int main()
{
            fooBar(1);
            foo();
}
void print(double) { std::cout << "d\n"; }
void print(int ) { std::cout << "i\n"; }