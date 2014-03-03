template<class... pack1, class T>
void f1(T n, pack1... args) {}
 
template<class... pack1, class T>
void f2(pack1... args, T n) {}
 
template<int...> struct T {};
 
template<int... pack1, int N, int... pack2>
void g1(const T<N, pack1...>& arg1, const T<N, pack2...>&) {}
 
template<int... pack1, int N, int... pack2>
void g2(const T<pack1..., N>& arg1, const T<N, pack2...>&) {}
 
int main()
{
    f1(1,2,3,4); // okay, N=1, pack1={2,3,4}
//  f2(1,2,3,4); // error: parameter pack in f2's parameter list is not last
 
    T<1,2> t1;
    T<1,-1,0> t2;
    g1(t1, t2); // okay, N=1, pack1 = {2}, pack2={-1,0}
//  g2(t1, t2); // error: parameter pack in g2's first argument's template
                // parameter list is not last
}