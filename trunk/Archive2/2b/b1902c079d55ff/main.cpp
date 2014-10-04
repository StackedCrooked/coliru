#include <type_traits>

template<class T, class U, typename std::enable_if<std::is_base_of<T, U>(), int>::type = 0>
void f(T, U){}

int main()
{
    
}