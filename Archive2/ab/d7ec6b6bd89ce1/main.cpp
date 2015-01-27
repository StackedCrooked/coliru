struct A {};

struct B {
    explicit B(A) {}
};

struct C {
	C(A a):
		b(a)
	{
		static_assert(std::is_convertible<A, decltype(b)>, "Must be convertible.");
	}
	B b;
};

struct D {
	D(A a):
		b(implicit_cast(a))
	{
	}
	B b;
};