#include <type_traits>

void overloaded(int) {}
void overloaded() {}

template<typename ...P, typename R>
auto deduce(R (P...)) -> R (&&)(P...);

template<typename ...P>
using full_type = typename std::remove_reference<
   decltype(deduce<P...>(&overloaded))>::type;

int main ()
{
	full_type<int> a;
	full_type<> b;
}
