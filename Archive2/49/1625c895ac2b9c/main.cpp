#include <iostream>

template<typename T1>
struct Outer
{
    void foo()
    {
        std::cout << "Works!" << std::endl;
    }

    Outer() : inner( ) 
    {
    }

    template<typename T2, void (T2::*f)()>
    struct Inner
    {
        Inner( )
        {
        }
        
        void callOut(T2& obj) const
        {
            (obj.*f)();
        }
    };

    Inner<Outer,&Outer::foo> inner;
};

int main()
{
    Outer<int> outer;
    outer.inner.callOut(outer);
}