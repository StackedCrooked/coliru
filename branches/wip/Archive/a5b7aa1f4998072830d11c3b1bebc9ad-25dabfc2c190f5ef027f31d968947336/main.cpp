#include <utility>
 
struct A {
    A(unsigned) {}  
};
 
template <typename ... Args>
A construct(Args&& ... args)
{
    return A{ std::forward<Args>(args)... };
}
 
int main()
{
    A a{ 10 };
    A aa{ construct(10) }; // main.cpp:10: error: non-constant-expression cannot be narrowed from type 'int' to 'unsigned int' in initializer list [-Wc++11-narrowing]
}