#include <iostream>
#include <vector>

struct A
{
    A() { }
	A(A&&) = delete;
	A(const A&) = delete;
};

struct B : A
{
	B() : A() { }
	B(B&&) : A() { }
	B(const B&) : A() { }
};

template<typename T>
struct allocator : std::allocator<T>
{
    using std::allocator<T>::allocator;
	using std::allocator<T>::construct;

	template<typename U>
	void construct(U* p, U&&) { construct(p); }

	template<typename U>
	void construct(U* p, const U&) { construct(p); }

	template<typename U>
	struct rebind { using other = allocator<U>; };
};

template<>
struct allocator<void> : std::allocator<void> { };

template<typename C, size_t N = 100>
void test()
{
	C c;
	c.reserve(N);
	for (size_t i = 0; i < N; ++i)
		c.emplace_back();
}

int main ()
{
	test<std::vector<B> >();
	test<std::vector<A, allocator <A> > >();
}
