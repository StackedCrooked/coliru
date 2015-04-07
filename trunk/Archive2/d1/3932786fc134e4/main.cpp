struct A
{
};
struct B
{
};

template <typename T>
auto f (B&b)->decltype(g (b, T ()))
{
    return g (b, T {});
}

void g (B&b, A)
{
}


void g (B&b, int)
{
}

int main ()
{ 
    B b;
  f<A> (b);
  f<int> (b);
}
