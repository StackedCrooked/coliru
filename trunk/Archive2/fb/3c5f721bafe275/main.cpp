#include <iostream>
#include <type_traits>
 
int main()
{
    printf("blah");
    int i = 123;
    int& ri = i;
    typedef std::add_pointer<decltype(i)>::type IntPtr;
    typedef std::add_pointer<decltype(ri)>::type IntPtr2;
    IntPtr pi = &i;
    std::cout << "i = " << i << "\n";
    std::cout << "*pi = " << *pi << "\n";
 
    static_assert(std::is_pointer<IntPtr>::value, "IntPtr should be a pointer");
    static_assert(std::is_same<IntPtr, int*>::value, "IntPtr should be a pointer to int");
    static_assert(std::is_same<IntPtr2, IntPtr>::value, "IntPtr2 should be equal to IntPtr");
 
    typedef std::remove_pointer<IntPtr>::type IntAgain;
    IntAgain j = i;
    std::cout << "j = " << j << "\n";
 
    static_assert(!std::is_pointer<IntAgain>::value, "IntAgain should not be a pointer");
    static_assert(std::is_same<IntAgain, int>::value, "IntPtr should be equal to int");
}