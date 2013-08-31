struct _Nil;

template<class Fty>
struct result_of{};

template<class F>
struct result_of<F()>{};

template<class F, class A0>
struct result_of<F(A0)>{};

template<class F, class A0, class A1>
struct result_of<F(A0, A1)>{};

int main()
{
}