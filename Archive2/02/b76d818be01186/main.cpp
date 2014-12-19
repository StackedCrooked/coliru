#include <array>
#include <iostream>
#include <tuple>
#include <utility>

// std::array to std::tuple

template<std::size_t N, typename T, std::size_t... Indices>
auto tuple_from_array_impl(T (&arr)[N], std::index_sequence<Indices...>)
    -> decltype(auto)
{
    return std::make_tuple(arr[Indices]...);
}

template<std::size_t N, typename T>
auto tuple_from_array(T (&arr)[N])
    -> decltype(auto)
{
    using Indices = std::make_index_sequence<N>;
    return tuple_from_array_impl(arr, Indices());
}

// print std::tuple to std::ostream

template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, std::index_sequence<Is...>){
  using swallow = int[];
  (void)swallow{ 0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)... };
}

template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
    -> std::basic_ostream<Ch, Tr>&
{
  os << "(";
  print_tuple(os, t, std::make_index_sequence<sizeof...(Args)>());
  return os << ")";
}

// Main

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    
    auto tpl = tuple_from_array(arr);
    std::cout << tpl;
}
