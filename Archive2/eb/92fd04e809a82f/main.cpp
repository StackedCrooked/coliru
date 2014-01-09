#include <vector>
#include <type_traits>

template<typename T>
struct allocator_wrapper : T { using T::T; };

template<class T, class A = std::allocator<T>>
using other_vector = std::vector<T, allocator_wrapper<A>>;

template<class... T>
struct other_vector_2 : std::vector<T...> { using std::vector<T...>::vector; };

template<typename> struct is_vector : std::false_type {};
template<typename... Ts> struct is_vector<std::vector<Ts...>> : std::true_type {};

int main()
{
    static_assert( is_vector<std::vector<int>>::value, "1" );
    static_assert( is_vector<other_vector<int>>::value, "2" );
    static_assert( is_vector<other_vector_2<int>>::value, "3" );
}
