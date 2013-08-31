#include <memory>
#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include <type_traits>

using std::cout;
using std::endl;

template<unsigned n, typename... Other> struct TypeHelper { };
template<unsigned n, typename T, typename... Other> struct TypeHelper<n, T, Other...>
{ typedef typename TypeHelper<n-1, Other...>::type type; };
template<typename T, typename... Other> struct TypeHelper<0, T, Other...>
{ typedef T type; };

template<typename... Args>
struct TMWParent
{
    template<unsigned n, typename E=void>
    struct TMW
    {
        static void func()
        { 
            cout<<"Default"<<endl;
            cout<<"Also, "<<std::is_same<typename TypeHelper<n-1, Args...>::type, bool>::value<<endl;
        }
    };
    template<unsigned n>
    struct TMW<n, typename std::enable_if<std::is_same<typename TypeHelper<n-1, Args...>::type, bool>::value, void>::type>
    {
        static void func() { cout<<"Spec"<<endl; }
    };
    
    static void func()
    {
        TMW<sizeof...(Args)>::func();
    }
};

int main()
{
	cout<<std::boolalpha;

    TMWParent<int, float, bool>::func();
}