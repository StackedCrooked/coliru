template <
    typename T,
	template <typename E> class Foo,
	typename E
> class Bar;

//template <
//	template <typename E> class Foo,
//	typename E
//> class Bar<int, Foo<E>, typename E>;

template <
    template <typename E> class Foo,
	typename E
> class Bar<int, Foo<E>>;

int main() {}