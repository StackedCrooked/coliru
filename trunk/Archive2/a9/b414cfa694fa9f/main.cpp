namespace A1
{
namespace A2
{
  class MyClass1;
}
}

namespace B1
{
namespace B2
{
  class MyClass2;
}
}


namespace A
{
template<typename T>
struct C
{
  static int member1_;
  static int member2_;
  static int member3_;
};

namespace T
{
using T1 = A1::A2::MyClass1;
using T2 = B1::B2::MyClass2;
}

template <> int C<T::T1>::member1_ = 5;
template <> int C<T::T1>::member2_ = 5;
template <> int C<T::T1>::member3_ = 5;


template <> int C<T::T2>::member1_ = 6;
template <> int C<T::T2>::member2_ = 6;
template <> int C<T::T2>::member3_ = 6;
}

int main(){}