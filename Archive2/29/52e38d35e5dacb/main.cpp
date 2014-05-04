struct delta
{
    template<typename I>
	void inc(I& i) { ++i; }
    
    template<typename I>
    constexpr I next(I i) { inc(i); return i; }
};

template<int I>
struct A {};

int main ()
{
	A<delta{}.next(4)>{};
}
