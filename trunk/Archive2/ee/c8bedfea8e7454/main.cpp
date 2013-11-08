#include <iostream>
 
struct Empty {};
 
struct Foo {
     int f2;
     float f1;
     char c;
};
 
int main()
{
    std::cout << "alignment of empty class: " << alignof(Empty) << '\n'
              << "alignment of pointer : "    << alignof(char*)  << '\n'
              << "alignment of char : "       << alignof(char)  << '\n'
              << "alignment of Foo : "        << alignof(Foo)   << '\n' ;
}