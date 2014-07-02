#include <type_traits>

namespace detail
{
template<class F>
struct has_deducible_signature
{
    template<class G>
    static auto test(int) -> decltype(&G::operator(), void());
    template<class>
    static auto test(...) -> struct nat;
    
    using type = std::is_void<decltype(test<F>(0))>;
};
} // detail::

template<class F>
struct has_deducible_signature
    : detail::has_deducible_signature<F>::type{};
    
// =====

struct deducible
{
    int operator()(int){ return 0; }
};

struct not_deducible
{
    int operator()(int){ return 0; }
    int operator()(int, int){ return 0; }
};

static_assert(has_deducible_signature<deducible>() == true, "deducible");
static_assert(has_deducible_signature<not_deducible>() == false, "not_deducible");

int main(){}