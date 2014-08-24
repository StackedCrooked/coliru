
#define TYPE_AND_VALUE(x) decltype(x),x

#define MemFuncTypeAdapter(x) MemFuncTypeAdapterStruct<TYPE_AND_VALUE(x)>

extern "C" 
{
    int (*cfunc)(struct A*, int);
}

template <typename MemFuncType> struct MemFuncTypes;
template <typename Class, typename Ret, typename... Args> 
struct MemFuncTypes<Ret (Class::*)(Args...)>
{
    using RetType = Ret;
    using ClassType = Class;
};

template <typename MemFuncType, MemFuncType memFunc>
struct MemFuncTypeAdapterStruct
{
    using RetType = typename MemFuncTypes<MemFuncType>::RetType;
    using ClassType = typename MemFuncTypes<MemFuncType>::ClassType;
    
    template <typename... Args>
    static RetType func (ClassType* c, Args... args) 
    {
        return (c->*memFunc)(args...);
    }
};

struct A
{
    A() : a(33) {};
    int a;
    int plus (int b) { return a + b; }
};

int main ()
{
    MemFuncTypeAdapter(&A::plus) aplus;
    A a;
    aplus.func(&a, 22);
    
    cfunc = &MemFuncTypeAdapter(&A::plus)::func; //<- C interface here

}