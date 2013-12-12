#include <memory>
#include <iostream>
#include <string>
 
int main()cvcv
{
    std::allocator<int> a1; // default allocator for ints
    int* a = a1.allocate(10); // space for 10 ints
 
    a[9] = 7;
 
    std::cout << a[9] << '\n';
 
    a1.deallocate(a, 10);
 
    // default allocator for strings
//    std::allocator<std::string> a2;
 
    // same, but obtained by rebinding from the type of a1
//    decltype(a1)::rebind<std::string>::other a2;
 
    // same, but obtained by rebinding from the type of a1 via allocator_traits
    std::allocator_traits<decltype(a1)>::rebind_alloc<std::string> a2;
 
    std::string* s = a2.allocate(2); // space for 2 string
 
    a2.construct(s, "foo");
    a2.construct(s + 1, "bar");
 
    std::cout << s[0] << ' ' << s[1] << '\n';
 
    a2.destroy(s);
    a2.destroy(s + 1);
    a2.deallocate(s, 2);
}