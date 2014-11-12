#include <iostream>
#include <functional>
#include <type_traits>
#include <memory>

using namespace std;

template<typename U, 
    typename F = typename std::enable_if<std::has_virtual_destructor<U>::value, U>::type>
using checked_delete = std::default_delete<U>;

template<typename T>
using checked_unique_ptr = unique_ptr<T, checked_delete<T>>;

struct A
{
    virtual ~A() 
    {
        cout << "~A()" << endl;
    }
};

struct B : A
{
    
};

int main()
{
    checked_unique_ptr<A> cd { new B{} };
}
