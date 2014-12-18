template <typename T> struct identity { typedef T type; };

template <typename C, typename T>
struct make_member_function_pointer;
template <typename C, typename R, typename Arg1>
struct make_member_function_pointer<C,R(Arg1)> : identity<R(C::*)(Arg1)> {};
template <typename C, typename R, typename Arg1, typename Arg2>
struct make_member_function_pointer<C,R(Arg1,Arg2)> : identity<R(C::*)(Arg1,Arg2)> {};
template <typename C, typename R, typename Arg1, typename Arg2, typename Arg3>
struct make_member_function_pointer<C,R(Arg1,Arg2,Arg3)> : identity<R(C::*)(Arg1,Arg2,Arg3)> {};

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

int main()
{
    SomeSmartStruct<MyClass, int(int)>::MemFuncPointerType pMemFunc = &MyClass::foo;
    SomeSmartStruct<MyClass, int(int)>::FunctionPointer pFunc = &bar;
}
