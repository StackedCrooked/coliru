enum FooValueT { ONE, ZERO };

struct Foo
{ 
    template <typename T = int>
    friend FooValueT operator+(FooValueT, FooValueT)
    {
        return FooValueT::ONE;
    }
};

int main()
{
    FooValueT::ONE + FooValueT::ZERO;
}
