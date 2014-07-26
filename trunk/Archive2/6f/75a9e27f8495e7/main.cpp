#include <array>
#include <type_traits>
#include <vector>

template<class T> struct matched : std::false_type { };

template< template<class, std::size_t, class...> class Container
    , class Type
    , std::size_t N
    , class... Args > struct matched<Container<Type, N, Args...>> : std::true_type {
        constexpr static int size = N;
    };

template
    < class Container, typename=std::enable_if_t<matched<std::decay_t<Container>>::value> >
auto func(std::size_t i, Container&& container) -> decltype(container[0]) { 
    //                                              ^^
    static_assert(matched<std::decay_t<Container>>::size >= 40 && matched<std::decay_t<Container>>::size <= 42, "bla bla bla");
    return container[i];
}
int main()
{
   std::array<float, 41> c = { 0 };
   const std::array<float, 41> d = { 0 };
   func(1, c);
   func(1, d);
   std::vector<float> e(41);
   func(1, e);
   func(1, std::array<float, 41> { 0 });
   std::array<float, 2> f = { 0 };
   func(1, f);
   return 0;
}