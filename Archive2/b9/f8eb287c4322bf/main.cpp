template <typename T1, typename T2, typename T3>
struct A
{
    A<T1, T2, T3> f1(){ return A<T1, T2, T3>();}
    A f2(){ return A();}
};

int main()
{
}
