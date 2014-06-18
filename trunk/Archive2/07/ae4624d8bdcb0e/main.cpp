

template<bool> struct A;
// explicit specializations for true and false
template<> struct A<true>
{ /* whatever */ };
template<> struct A<false>
{ /* whatever */ };



#ifdef A_TRUE
#define A_TRUE_VALUE true
#else
#define A_TRUE_VALUE false
#endif

struct B
{
  static A<A_TRUE_VALUE> ainstance;
};

A<A_TRUE_VALUE> B::ainstance;