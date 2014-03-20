template<int i, class T> class A:A<i, A<i, T> >
{ A<i-1, T> x;};
int main(){A<500, int> x;}