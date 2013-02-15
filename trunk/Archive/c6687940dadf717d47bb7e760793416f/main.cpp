struct A
{
    int start;
};

struct B
{
    int x;
    A a;
};

template <typename T>
void modifyInt(T& item, int T::* var)
{
    (item.*var) = 5;
}


int main()
{
    B b;
    //compiles:
    modifyInt(b, &B::x);
    
    //does not compile, but we should be allowed to do it =<
    //modifyInt(b, &B::a.start);
}