#define REM_CTOR(...) __VA_ARGS__

#define SPEC(var, cv, ref) \
template <typename R, typename... Args> \
struct strip_function_qualifiers<R(Args... REM_CTOR var) \
    cv ref > \
{using type = R(Args... REM_CTOR var);};

#define REF(var, cv) SPEC(var, cv,) SPEC(var, cv, &) \
                     SPEC(var, cv, &&)

#define CV(var) REF(var,) REF(var, const) \
                REF(var, volatile) REF(var, const volatile)

template <typename> struct strip_function_qualifiers;

CV(()) CV((,...))

template <typename T>
using strip_t = typename strip_function_qualifiers<T>::type;

#include <type_traits>
int main()
{
    static_assert( std::is_same<void()   , strip_t<void() const>>{}, "" );
	static_assert( std::is_same<void()   , strip_t<void() const&&>>{}, "" );
	static_assert( std::is_same<void(...), strip_t<void(...) const volatile&&>>{}, "" );
}
