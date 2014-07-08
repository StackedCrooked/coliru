template<int I>
struct A
{
  enum { val = A<I+1>::val };
};

int i = A<1>::val;