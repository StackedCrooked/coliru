#include <tuple>
 
template <class... Args>
struct type_list
{
   template <std::size_t N>
   using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
};
 
int main()
{
   type_list<int, char, bool>::type<2> x = true;
}