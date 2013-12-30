#include <iostream>
struct Empty {};
struct Bit {unsigned bit:1; };
int main()
{
    Empty e;    
    char *t;
    stcpy(t,"002020070210675       20070112OPTMAADV            20070112SUCCES    20070112SO1                                                                                                                                                                                A");
    std::cout << "size of empty class: "     << sizeof e        << '\n'              
              << "size of pointer A : "        << sizeof &t       << '\n'
//            << "size of function: "        << sizeof(void())  << '\n'  // compile error
//            << "size of incomplete type: " << sizeof(int[])   << '\n'  // compile error
//            << "size of bit field: "       << sizeof b.bit    << '\n'  // compile error
              << "size of array of 10 int: " << sizeof(int[10]) << '\n';
}