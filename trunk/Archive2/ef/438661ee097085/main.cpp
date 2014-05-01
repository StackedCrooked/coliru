#include <utility>

struct A
{
    template<typename T> explicit operator T&&       () &&;
	template<typename T> explicit operator T&        () &;
	template<typename T> explicit operator const T&  () const&;

	template<typename T> T&&       cast() &&;
	template<typename T> T&        cast() &;
	template<typename T> const T&  cast() const&;
};

template<typename T> T&&       cast(A&&);
template<typename T> T&        cast(A&);
template<typename T> const T&  cast(const A&);

struct B
{
	template<typename T> operator T&&       () &&;
	template<typename T> operator T&        () &;
	template<typename T> operator const T&  () const&;
};

struct C {};

template<typename T>
struct flexi
{
	static constexpr bool all() { return true; }

	template<typename A, typename... B>
	static constexpr bool all(A a, B... b) { return a && all(b...); }

	template<typename... A>
	using convert_only = typename std::enable_if<
		all(std::is_convertible<A, T>{}...),
	int>::type;

	template<typename... A>
	using explicit_only = typename std::enable_if<
		!all(std::is_convertible<A, T>{}...) &&
		all(std::is_constructible<T, A>{}...),
	int>::type;

	template<typename... A, convert_only<A...> = 0>
	flexi(A&&...);

	template<typename... A, explicit_only<A...> = 0>
	explicit flexi(A&&...);
};

using D = flexi<int>;

int main ()
{
	A a;
	B b;

	C member_move = std::move(a).cast<C>();  // U1. (ugly) OK
	C member_temp = A{}.cast<C>();           // (same)

	C non_member_move(cast<C>(std::move(a)));  // U2. (ugly) OK
	C non_member_temp(cast<C>(A{}));           // (same)

	C direct_move_expl(std::move(a));  // 1. call to constructor of C ambiguous
	C direct_temp_expl(A{});           // (same)

	C direct_move_impl(std::move(b));  // 2. call to constructor of C ambiguous
	C direct_temp_impl(B{});           // (same)

	C copy_move_expl = std::move(a);  // 3. no viable conversion from A to C
	C copy_temp_expl = A{};           // (same)

	C copy_move_impl = std::move(b);  // 4. OK
	C copy_temp_impl = B{};           // (same)

	D direct_move_expl_flexi(std::move(a));  // F1. call to constructor of D ambiguous
	D direct_temp_expl_flexi(A{});           // (same)

	D direct_move_impl_flexi(std::move(b));  // F2. OK
	D direct_temp_impl_flexi(B{});           // (same)

	D copy_move_expl_flexi = std::move(a);  // F3. no viable conversion from A to D
	D copy_temp_expl_flexi = A{};           // (same)

	D copy_move_impl_flexi = std::move(b);  // F4. conversion from B to D ambiguous
	D copy_temp_impl_flexi = B{};           // (same)

	D&& ref_direct_move_expl_flexi(std::move(a));  // R1. OK
	D&& ref_direct_temp_expl_flexi(A{});           // (same)

	D&& ref_direct_move_impl_flexi(std::move(b));  // R2. initialization of D&& from B ambiguous
	D&& ref_direct_temp_impl_flexi(B{});           // (same)

	D&& ref_copy_move_expl_flexi(std::move(a));  // R3. OK
	D&& ref_copy_temp_expl_flexi(A{});           // (same)

	D&& ref_copy_move_impl_flexi = std::move(b);  // R4. initialization of D&& from B ambiguous
	D&& ref_copy_temp_impl_flexi = B{};           // (same)
}
