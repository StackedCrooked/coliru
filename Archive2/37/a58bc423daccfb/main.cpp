template<int I = 0, int J = 0> struct A : A<I+1>, A<I+1, J+1>{};
template<int J> struct A<500,J>{};
A<0> a;