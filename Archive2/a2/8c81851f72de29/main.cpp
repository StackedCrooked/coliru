template<class Type, class ValueT>
class ImplAdd
{
   template<typename T>
   friend Type operator+(T, T)
   {
      return Type{};
   }
};

enum class FooValueT { ONE, ZERO };

class Foo : ImplAdd<Foo, FooValueT>
{
public:
   Foo() {}
   Foo(FooValueT) {}
};

int main()
{
   Foo f = FooValueT::ONE + FooValueT::ZERO;
}