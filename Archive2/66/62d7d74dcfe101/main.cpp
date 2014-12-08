#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

template<int... vals>
struct List{};

template<int X, typename List>
struct Add;

template<int X, int ... Vals>
struct Add<X, List<Vals...>>
{
  using type = List<X, Vals...>;
};

template<typename List>
struct Get{};

template<int X, int ... Vals>
struct Get<List<X, Vals...>>
{
  using head = List<X>;
  using tail = List<Vals...>;
};

int main()
{
    using data_t = List<10,20,300>;
    std::cout << typeid(Get< Get< data_t>::tail>::tail).name();
}
