template <typename C, typename T>
struct make_member_function_pointer;

template <typename C, typename R, typename... Args>
struct make_member_function_pointer<C,R(Args...)>
{
    using type = R(C::*)(Args...);
};

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
