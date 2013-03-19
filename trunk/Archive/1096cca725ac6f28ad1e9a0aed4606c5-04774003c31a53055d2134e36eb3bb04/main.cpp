struct _Nil;

template<class F, class A0 = _Nil, class A1 = _Nil, class A2 = _Nil>
struct result_of{};

template<class F>
struct result_of<F, _Nil>{};

template<class F, class A0>
struct result_of<F, A0, _Nil>{};

template<class F, class A0, class A1>
struct result_of<F, A0, A1, _Nil>{};

int main()
{
}