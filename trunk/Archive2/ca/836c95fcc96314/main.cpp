#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

#define AS_LAMBDA(NAME)                                    \
    ([]{                                                   \
        struct {                                           \
            template<typename... Args>                     \
            auto operator()(Args&&... args)                \
            -> decltype(NAME(std::forward<Args>(args)...)) \
            { return NAME(std::forward<Args>(args)...); }  \
        } f;                                               \
        return f;                                          \
    }())

int main()
{
    constexpr int xs[]{1,  2, 3,  4, 5};
    constexpr int ys[]{0, 10, 1, 20, 5};

    using std::begin; using std::end;
    std::transform(begin(xs), end(xs), begin(ys),
                   std::ostream_iterator<int>(std::cout, " "),
                   AS_LAMBDA(std::max));
}
