#include <utility>
#include <functional>
#include <tuple>

template<class T>
struct make_tuple_ref_unwrapper { typedef T type;  constexpr const T& operator()(const T& t){return t;}};
template<class T>
struct make_tuple_ref_unwrapper<std::reference_wrapper<const T>> { typedef const T& type; constexpr const T& operator()(const T& t) {return t;}};
template<class T>
struct make_tuple_ref_unwrapper<std::reference_wrapper<T>> { typedef T& type; constexpr T& operator()(T& t) {return t;}};

template<class...Ts>
constexpr std::tuple<typename make_tuple_ref_unwrapper<Ts>::type...> my_make_tuple(Ts...vs) 
{return std::tuple<typename make_tuple_ref_unwrapper<Ts>::type...>(make_tuple_ref_unwrapper<Ts>()(vs)...);}




int main() {
    auto t = my_make_tuple(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30);
    auto u = my_make_tuple("HI",std::ref(t));
}