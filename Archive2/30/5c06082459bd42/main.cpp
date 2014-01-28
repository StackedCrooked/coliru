#include <iostream>
struct Empty {
    char myarray[4294967298];
};
struct Bit {unsigned bit:1; };
int main()
{
    Empty e;
    unsigned int foo = sizeof(e);
    //Bit b;
    std::cout << "size of empty class: "     << sizeof e        << '\n'
              << "size of pointer : "        << sizeof &e       << '\n'
//            << "size of function: "        << sizeof(void())  << '\n'  // compile error
//            << "size of incomplete type: " << sizeof(int[])   << '\n'  // compile error
//            << "size of bit field: "       << sizeof b.bit    << '\n'  // compile error
              << "size of array of 10 int: " << sizeof(int[10]) << '\n'
              << "size of foo: " << sizeof(foo) << '\n'
              << "foo: " << foo << '\n';
              
}