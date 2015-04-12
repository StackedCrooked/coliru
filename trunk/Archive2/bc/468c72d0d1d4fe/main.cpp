#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
 
struct A {
    int n;
    std::string s1;
    // user-defined copy assignment, copy-and-swap form
    A& operator=(A other) {
        std::cout << "copy assignment of A\n";
        std::swap(n, other.n);
        std::swap(s1, other.s1);
        return *this;
    }
};
 
struct B : A {
    std::string s2;
    // implicitly-defined copy assignment
};
 
struct C {
     std::unique_ptr<int[]> data;
     std::size_t size;
     // non-copy-and-swap assignment
     C& operator=(const C& other) {
         // check for self-assignment
         if(&other == this)
             return *this;
         // reuse storage when possible
         if(size != other.size)
             data.reset(new int[other.size]);
         std::copy(&other.data[0],
                   &other.data[0] + std::min(size, other.size),
                   &data[0]);
         return *this;
     }
     // note: copy-and-swap would always cause a reallocation
};
 
int main()
{
    A a1, a2;
    std::cout << "a1 = a2 calls ";
    a1 = a2; // user-defined copy assignment
 
    B b1, b2;
    b2.s1 = "foo";
    b2.s2 = "bar";
    std::cout << "b1 = b2 calls ";
    b1 = b2; // implicitly-defined copy assignment
    std::cout << "b1.s1 = " << b1.s1 << " b1.s2 = " << b1.s2 <<  '\n';
}