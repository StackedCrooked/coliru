#include <utility>
#include <iostream>
 
template <class T>
void array_to_pointer(T)
{
    static_assert(std::is_same<T, int*>::value, "");
}
 
template <class T>
void func_to_pointer(T)
{
    static_assert(std::is_same<T, void(*)(int)>::value, "");
}
 
template <class T>
void cv_ignored(T)
{
    static_assert(std::is_same<T, int>::value, "");
}
 
void foo(int) {}
 
int main()
{
    int a[3];
    static_assert(std::is_same<decltype(a), int[3]>::value, "");
    array_to_pointer(a); // array to pointer conversion: T = 'int*'
 
    static_assert(std::is_same<decltype(foo), void(int)>::value, "");
    func_to_pointer(foo); // function to pointer conversion: T = 'void(*)(int)'
 
    const int b = 13;
    static_assert(std::is_same<decltype(b), const int>::value, "");
    cv_ignored(b); // cv-qualifier ignored: T = 'int'
 
    std::cout << "done\n";
}