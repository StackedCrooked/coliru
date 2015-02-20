#include <iostream>
#include <tuple>
#include <utility>
#include <array>

    template<class Tuple>
    struct tuple_printer {
      enum { size = std::tuple_size< std::decay_t<Tuple> >{} };
      using indexes = std::make_index_sequence<size>;
      Tuple&& tuple;
      friend std::ostream& operator<<(std::ostream& stream, tuple_printer&& self) {
        std::move(self).print_to(indexes{}, stream);
        return stream;
      }
      template<size_t...Is>
      void print_to(std::index_sequence<Is...>,std::ostream& stream)&& {
        int _[]={0,((void)(
          stream << std::get<Is>(std::forward<Tuple>(tuple))
        ),0)...};
        (void)_;
      }
    };
    template<class Tuple>
    tuple_printer<Tuple> print_tuple(Tuple&& t){return {std::forward<Tuple>(t)};}


int main() {
    std::array<int, 3> foo = {{1,2,3}};
    auto tup = std::make_tuple<double, int, char>( 3.14, -1, 'a' );
    std::cout << print_tuple(foo) << '\n';
    std::cout << print_tuple(tup) << '\n';
}