enum FooValueT { ONE, ZERO };

struct Foo
{ 
   friend FooValueT operator+(FooValueT, FooValueT)
   {
      return FooValueT::ONE;
   }
};

int main()
{
    FooValueT::ONE + FooValueT::ZERO;
}
