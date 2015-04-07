#include <type_traits>

namespace sensible {

template<typename Cond, typename Then = void>
struct enable_if: std::enable_if<Cond::value> {};

template<typename Cond, typename Then = void>
using enable_if_t = typename enable_if<Cond, Then>::type;

} // sensible

enum struct enabled {};


template<typename Arg, std::enable_if_t<std::is_integral<Arg>::value, enabled>...>
void helpless(Arg) {}

template<typename Arg, sensible::enable_if_t<std::is_integral<Arg>, enabled>...>
void helpful(Arg) {}

int main()
{
    helpless(0.0);
    helpful(0.0);
}