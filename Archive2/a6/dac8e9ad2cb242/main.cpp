#include <iostream>
#include <utility>
#include <tuple>

    template<bool b>
    using bool_t = std::integral_constant<bool, b>;

    template<int I, typename ... Tlist>
    void print(std::ostream& s, std::tuple<Tlist...> const& t, std::false_type) {
      // no more printing
    }

    template<int I, typename ... Tlist>
    void print(std::ostream& s, std::tuple<Tlist...> const& t, std::true_type) {
      s << std::get<I>(t) << ", ";
      print<I+1>(s, t, bool_t<((I+1) < sizeof...(Tlist))>{});
    }
    template<typename ... Tlist>
    std::ostream& operator<<(std::ostream& s, std::tuple<Tlist...> const& t)
    {
      print<0>(s,t, bool_t<(0 < sizeof...(Tlist))>{});
      return s;
    }

int main() {
    std::tuple<int, double> x(-1, 3.14);
    std::cout << x;
}