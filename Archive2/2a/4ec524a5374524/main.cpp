struct delta
{
    template<typename I>
	constexpr void inc(I& i) { ++i; }
    
    template<typename I>
    constexpr I next(I i) { return inc(i), i; }
};

template<int I>
struct A {};

int main ()
{
	A<delta{}.next(4)>{};
}
