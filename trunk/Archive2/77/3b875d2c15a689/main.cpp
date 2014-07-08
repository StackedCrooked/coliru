template<bool> struct test;
template<> struct test<true>{ using type = void; };

template<bool B>
typename test<B>::type f(int){}

template<bool>
void f(...){}

int main()
{
    f<true>(0);
    f<false>(0);
}