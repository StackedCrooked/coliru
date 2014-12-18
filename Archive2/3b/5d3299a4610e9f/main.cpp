#include <iostream>

template<typename T1>
struct Outer
{
    void foo()
    {
        std::cout << "Works!" << std::endl;
    }

    Outer() : inner(&Outer::foo) 
    {
    }

    template<typename T2>
    struct Inner
    {
        Inner(void (T2::*f)())
            : fn(f)
        {
        }
        
        void callOut(T2& obj) const
        {
            (obj.*fn)();
        }
        
        void (T2::*fn)();
    };

    Inner<Outer> inner;
};

int main()
{
    Outer<int> outer;
    outer.inner.callOut(outer);
}