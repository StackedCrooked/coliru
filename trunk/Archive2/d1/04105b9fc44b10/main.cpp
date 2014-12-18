#include <boost/preprocessor.hpp>

template <typename T> struct identity { typedef T type; };

template <typename C, typename T>
struct make_member_function_pointer;

#define MAKE_MEMBER_FUNCTION_POINTER(z, n, data) \
    template <typename C, typename R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename Arg)>\
    struct make_member_function_pointer<C,R(BOOST_PP_ENUM_PARAMS(n, Arg))> : identity<R(C::*)(BOOST_PP_ENUM_PARAMS(n, Arg))> {};
#define BOOST_PP_LOCAL_MACRO(n) MAKE_MEMBER_FUNCTION_POINTER(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS (0, 20) // 20 is the limit of params
#include BOOST_PP_LOCAL_ITERATE()

template <typename T, typename F>
struct SomeSmartStruct
{
    typedef typename make_member_function_pointer<T,F>::type MemFuncPointerType;
    typedef F* FunctionPointer;
};

struct MyClass
{
    int foo(int) {return 0;}
};
int bar(int) {return 0;}
int bar10(int,int,int,int,int,int,int,int,int,int) {return 0;}

int main()
{
    SomeSmartStruct<MyClass, int(int)>::MemFuncPointerType pMemFunc = &MyClass::foo;
    SomeSmartStruct<MyClass, int(int)>::FunctionPointer pFunc = &bar;
    SomeSmartStruct<MyClass, int(int,int,int,int,int,int,int,int,int,int)>::FunctionPointer pFunc10 = &bar10;
}
