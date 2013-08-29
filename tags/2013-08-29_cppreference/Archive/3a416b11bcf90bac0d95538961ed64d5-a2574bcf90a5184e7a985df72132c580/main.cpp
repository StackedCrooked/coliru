#include <tuple>
#include <string>
#include <sstream>
#include <type_traits>

template<bool I>
using Bool = std::integral_constant<bool, I>;

template<typename T>
using EnableIf = typename std::enable_if<T::value>::type;

namespace detail {
template<size_t N = 0, class Elem, class Traits, typename... Args, EnableIf<Bool<(N >= sizeof...(Args))>>...>
inline void helper(std::basic_ostream<Elem,Traits>& out, const size_t i, const std::tuple<Args...>& tup) {}
template<size_t N = 0, class Elem, class Traits, typename... Args, EnableIf<Bool<(N < sizeof...(Args))>>...>
inline void helper(std::basic_ostream<Elem,Traits>& out, const size_t i, const std::tuple<Args...>& tup) {
    if(i == N) {
        out << std::get<N>(tup);
    }
    else {
        helper<N+1, Elem, Traits, Args...>(out, i, tup);
    }
}
} // detail

template<size_t N = 0, typename... Args>
std::string format(const std::string& str, Args&&... args) {
    if(sizeof...(args) < 1)
        return str;
    auto tup = std::make_tuple(std::forward<Args>(args)...);
    auto first = std::begin(str);
    auto last = std::end(str);
    size_t index = 0;
    std::ostringstream out;
    while(first != last) {
        if(*first != '{') {
            out << *first++;
            continue;
        }
        else { // If it's a { character
            auto check = first;
            ++check;
            index = 0;
            // Keep incrementing the index.
            while(check != last && (*check >= '0' && *check <= '9')) {
                if(*check == '}')
                    break;
                index *= 10;
                index += ((*check) - '0');
                ++check;
            }
            if(*check++ == '}') {
                detail::helper(out, index, tup);
            }
            first = check;
        }
    }
    std::string result = out.str();
    return result;
}

#include <iostream>

int main() {
    auto i = format("{0} + {0} = {1}", 2, 4);
    std::cout << i;
}
