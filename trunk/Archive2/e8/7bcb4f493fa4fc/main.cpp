#include <type_traits>
#include <iostream>

//-----------------------------------------------------------------------------

template <typename M> struct member_type_t { };
template <typename M> using  member_type = typename member_type_t <M>::type;

template <typename T, typename C>
struct member_type_t <T C::*> { using type = T;};

//-----------------------------------------------------------------------------

template<typename>
struct member_class_t;

template<typename M>
using member_class = typename member_class_t <M>::type;

template<typename R, typename C, typename... A>
struct member_class_t <R(C::*)(A...)> { using type = C; };

template<typename R, typename C, typename... A>
struct member_class_t <R(C::*)(A...) const> { using type = C const; };

// ...other qualifier specializations

//-----------------------------------------------------------------------------

template <typename C, typename S>
struct member_ptr_t;

template <typename C, typename S>
using member_ptr = typename member_ptr_t <C, S>::type;

template <typename C, typename R, typename ...A>
struct member_ptr_t <C, R(A...)> { using type = R (C::*)(A...); };

template <typename C, typename R, typename ...A>
struct member_ptr_t <C const, R(A...)> { using type = R (C::*)(A...) const; };

// ...other qualifier specializations

//-----------------------------------------------------------------------------

template <typename T>
struct is_foo {
private:
	template<
		typename Z,
		typename M = decltype(&Z::foo),
		typename C = typename std::decay<member_class<M>>::type,
		typename S = member_type<M>
	>
	using pattern = member_ptr<C const, void()>;

	template<typename U, U> struct helper{};

	template <typename Z> static auto test(Z z) -> decltype(
		helper<pattern<Z>, &Z::foo>(),
		// All other requirements follow..
		std::true_type()
	);

	template <typename> static auto test(...) -> std::false_type;

public:
	enum { value = std::is_same<decltype(test<T>(std::declval<T>())),std::true_type>::value };
};

//-----------------------------------------------------------------------------

struct A { void foo() const; };
struct A1 : public A {};

struct B { void foo(); };
struct C { int foo() const; };

template <typename T>
struct D : public T {};

int main() {
	std::cout << "Good examples (should print 1)\n";
	std::cout << is_foo<A>::value << '\n';
	std::cout << is_foo<A1>::value << '\n';
	std::cout << is_foo<D<A>>::value << '\n';
	std::cout << is_foo<D<A1>>::value << '\n';

	std::cout << "Bad examples (should print 0)\n";
	std::cout << is_foo<B>::value << '\n';
	std::cout << is_foo<C>::value << '\n';
	std::cout << is_foo<D<B>>::value << '\n';
	std::cout << is_foo<D<C>>::value << '\n';
}