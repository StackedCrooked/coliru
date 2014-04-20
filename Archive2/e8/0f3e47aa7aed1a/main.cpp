#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdint>

namespace detail
{
        // a little overkill to have a functor here too, but it's a good habit™
    template <typename T = uintmax_t>
    struct to_bitmask_f
    {
        template <typename... Flags> struct result { typedef T type; };

        template <typename... Flags>
            typename result<Flags...>::type
            constexpr operator()(Flags... flags) const {
                static_assert(sizeof...(Flags) < std::numeric_limits<uintmax_t>::digits, "Too many flags for integral representation)");
                return impl(flags...);
            }

    private:
        constexpr static inline T impl() { return {}; }
        template <typename... Flags>
            constexpr static inline T impl(bool b, Flags... more) { 
            return (b?1:0) + (impl(more...) << (T(1)));
        }
    };
}

template <typename T = uintmax_t, typename... Flags>
    constexpr T combine(Flags... flags)
{
    return detail::to_bitmask_f<T>()(flags...);
}

void do_something(int i) { std::cout << "something " << i << "\n"; }
void do_something_else() { std::cout << "something else\n"; }

void f(bool cond1, bool cond2, bool cond3, bool cond4) {
    switch(combine(cond1, cond2, cond3, cond4))
    {
        case combine(1,1,1,0): do_something(1); break;
        case combine(1,1,0,1): do_something(2); break;
        case combine(1,0,1,1): do_something(3); break;
        case combine(0,1,1,1): do_something(4); break;
        default: 
            do_something_else();
            break;
    }
}

int main()
{
    f(1,0,1,0);
    f(1,0,0,1);
    f(0,1,1,0);
    f(0,1,0,1);
    f(0,1,1,1);
    f(1,1,1,1);
    f(1,1,1,0);
    f(0,0,0,0);
}

