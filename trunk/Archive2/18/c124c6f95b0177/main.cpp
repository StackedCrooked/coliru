#include <type_traits>

template<class Type, class ValueT>
class ImplAdd
{
   template<typename T>
   friend typename std::enable_if<std::is_same<T, ValueT>::value, Type>::type operator+(T, T)
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

struct A {};

int main()
{
   Foo f = FooValueT::ONE + FooValueT::ZERO;
}
