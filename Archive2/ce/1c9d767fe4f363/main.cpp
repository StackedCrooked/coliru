#include <type_traits>
#include <utility>

#define FAIL

namespace {

template<typename T>
struct implicit_cast_t {
    template<typename U, typename = std::enable_if_t<std::is_convertible<T, U>::value>>
	constexpr explicit operator U() const {
		return static_cast<T>(value);
	}
	
	T value;
};

template<typename T>
constexpr auto implicit_cast(T && value) {
	return implicit_cast_t<T &&>{ std::forward<T>(value) };
}

struct A {};
struct B {};

struct C {
	C() = default;
	explicit C(A) {}
	C(B) {}
};

struct Explicit {
	explicit Explicit(B b, A a):
		c1(b),
		c2(a) {
	}
	
	C c1;
	C c2;
};

struct Implicit {
	explicit Implicit(B b, A a):
		c1(implicit_cast(b))
		#if defined FAIL
		, c2(implicit_cast(a))
		#endif
		{
		static_cast<void>(a);
	}
	
	C c1;
	C c2;
};

struct Movable {
	Movable() = default;
	Movable(Movable &&) = default;
	Movable(Movable const &) = delete;
};

}	// namespace

auto main() -> int {
	A a;
	B b;
	Explicit e(b, a);
	Implicit i(b, a);
	double x(implicit_cast(5));
    static_cast<void>(x);
	
	Movable m1;
	Movable m2(implicit_cast(std::move(m1)));
	#if defined FAIL
	Movable m3(implicit_cast(m2));
	#endif
}