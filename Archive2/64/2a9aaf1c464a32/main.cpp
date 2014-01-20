#include <type_traits>

template <typename T>
struct is_complete_helper {
    template <typename U>
    static auto test(U*)  -> std::integral_constant<bool, sizeof(U) == sizeof(U)>;
    static auto test(...) -> std::false_type;
    using type = decltype(test((T*)0));
};

template <typename T>
struct is_complete : is_complete_helper<T>::type {};

struct A {};
struct B;

static_assert(is_complete<A>(), "A should be complete");
static_assert(!is_complete<B>(), "B should not be complete");
static_assert(is_complete<int>(), "int should be complete");

#include <iosfwd>
static_assert(!is_complete<std::fstream>(), "std::fstream should not be complete");

template <class T> struct hash;
template <>        struct hash<int> {};

// is_defined_hash_type definition...

enum Enum { A, B, C, D };

template <typename T>
struct is_defined_hash_type : public is_complete<hash<T>> {};

static_assert (  is_defined_hash_type<int> ::value, "hash<int> should be defined");
static_assert (! is_defined_hash_type<Enum>::value, "hash<Enum> should not be defined");
