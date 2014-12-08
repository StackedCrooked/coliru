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


template<int ...Vals>
void print(const List<Vals...> & )
{
    int arr[] = {Vals...};
    for( auto && i : arr)
    std::cout << i << " ";
}


int main()
{
//    auto a = {10,20,30};
    using data_t = List<10,20,300>;
//    std::cout << typeid(a).name();
//    std::cout << typeid(Get< Get< data_t>::tail>::tail).name();
    print( data_t{} );
}
