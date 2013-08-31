#include <type_traits>

template <int...> struct indexes {};

namespace {
    template<int a, int... other>
        constexpr indexes<a, other...> combine(indexes<other...> deduce) { return {}; }

    template<int a, int b, typename Enable = void> struct expand_span_; // primary

    template<int a, int b>
    struct expand_span_<a, b, typename std::enable_if< (a==b), void >::type> {
        static constexpr indexes<a> dispatch() { return {}; }
    };

    template<int a, int b>
    struct expand_span_<a, b, typename std::enable_if< (a!=b), void >::type> {
        static constexpr decltype(combine<a>(expand_span_<a+1, b>::dispatch())) dispatch() 
        {
            static_assert(a<=b, "invalid span");
            return combine<a>(expand_span_<a+1, b>::dispatch());
        }
    };

    template<int a, int b>
    constexpr auto expand_span() -> decltype(expand_span_<a,b>::dispatch()) {
        return expand_span_<a,b>::dispatch();
    }
}

template <int a, int b> using span = decltype(expand_span<a,b>());

////////////////////////////////////////////////////////////////
// using indirect template arguments
template<typename> struct indirect_work { };

void test_indirect()
{
    indirect_work<indexes<1,2,3,4>> x;
    indirect_work<span<1,4>>        y;

    x = y; // x and y are of identical types
}

////////////////////////////////////////////////////////////////
// using direct template arguments
template<int...> struct direct_work { };

template<int... direct> 
constexpr direct_work<direct...> make_work(indexes<direct...>)
{
    return {};
}

void test_direct()
{
    direct_work<1,2,3,4> x;
    auto y = make_work(indexes<1,2,3,4>{});
    auto z = make_work(span<1,4>{});

    x = y; // x and y are of identical types
    x = z; // x and z too
}

int main()
{
    test_indirect();
    test_direct();
}
