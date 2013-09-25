#include <cstdio>

template<typename T>
struct Outer
{
    struct InnerBase
    {
        virtual void foo(T const&) = 0;
        virtual void bar(T const&) {  };
    };

    struct InnerDerived : public InnerBase
    {
        void foo(T const&) override { std::printf("virtual call foo() worked\n"); }
        void bar(T const&) override { std::printf("virtual call bar() worked\n"); }
    };

    InnerBase* inner;
    Outer() : inner(new InnerDerived()) {  }
};

template<typename T>
void Outer<T>::InnerBase::foo(T const&) {};

struct NonLocalStruct { };

int main()
{
    struct LocalStruct { };

    Outer<NonLocalStruct> a;
    Outer<LocalStruct>    b;

    a.inner->foo(NonLocalStruct());     // fine
    a.inner->bar(NonLocalStruct());     // fine
    b.inner->foo(LocalStruct());        // causes error
    b.inner->bar(LocalStruct());        // fine

    return 0;
}