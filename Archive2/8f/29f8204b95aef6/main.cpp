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

void ac() { std::cout << "ac\n"; }
void ad() { std::cout << "ad\n"; }
void bc() { std::cout << "bc\n"; }
void bd() { std::cout << "bd\n"; }

void f(bool a, bool b, bool c, bool d) {
    switch(combine(a, b, c, d))
    {
        case combine(1,0,1,0): ac(); break;
        case combine(1,0,0,1): ad(); break;
        case combine(0,1,1,0): bc(); break;
        default: bd(); break;
    }
}

int main()
{
    f(1,0,1,0);
    f(1,0,0,1);
    f(0,1,1,0);
    f(0,1,0,1);
    // others:
    f(0,1,1,1);
    f(1,1,1,1);
    f(0,0,0,0);
}
