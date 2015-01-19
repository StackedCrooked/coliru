template<int I>
struct X { };

template<unsigned int U>
void foo(X<U>) { };

int main()
{
    auto x = X<4>{};
    foo(x);
}