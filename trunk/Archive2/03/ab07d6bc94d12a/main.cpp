#include <cstddef>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

// Build a tuple with the specified number
// if integer fields.
template <std::size_t N, typename... Ints>
struct tuple_type_builder {
  using type = typename tuple_type_builder<N - 1, int, Ints...>::type;
};

template <typename... Ints>
struct tuple_type_builder<0, Ints...> {
  using type = std::tuple<Ints...>;
};

template <std::size_t N>
using tuple_type = typename tuple_type_builder<N>::type;

// for (int i = 0; i <= 20; ++i) { M(i); }
#define M20 M(0); M(1); M(2); M(3); M(4); M(5); M(6); M(7); M(8); M(9); M(10); \
            M(11);M(12);M(13);M(14);M(15);M(16);M(17);M(18);M(19);M(20)

// Discriminated union of many many tuples of ints
struct lotsa_tuples {
  struct too_many_ints {};
  std::size_t how_many_ints;
  union many_tuples {
#define M(n) tuple_type<n> t##n
    M20;
#undef M
    many_tuples() {}
  } tuples;

  lotsa_tuples(std::size_t this_many_ints) :
    how_many_ints(this_many_ints) {
    switch(how_many_ints) {
#define M(n) case n: \
      ::new (&tuples.t##n) tuple_type<n>; \
      std::cout << "building tuple_type<" #n ">\n"; \
      break
    M20;
#undef M
    default:
      throw too_many_ints();
    }
  }

  ~lotsa_tuples() { destroy(); }

  lotsa_tuples(const lotsa_tuples& other) { copy(other); }
  lotsa_tuples& operator = (const lotsa_tuples& other) {
    destroy();
    copy(other);
    return *this;
  }

  lotsa_tuples(lotsa_tuples&& other) { move(std::move(other)); }
  lotsa_tuples& operator = (lotsa_tuples&& other) {
    destroy();
    move(std::move(other));
    return *this;
  }

private:
  void destroy() {
    switch(how_many_ints) {
#define M(n) case n: \
      std::cout << "destroying tuple_type<" #n ">\n"; \
      tuples.t##n.~tuple_type<n>(); \
      break
    M20;
#undef M
    default:
      throw too_many_ints();
    }
  }

  void copy(const lotsa_tuples& other) {
    how_many_ints = other.how_many_ints;
    switch(how_many_ints) {
#define M(n) case n: \
      std::cout << "copying tuple_type<" #n ">\n"; \
      ::new (&tuples.t##n) tuple_type<n>(other.tuples.t##n); \
      break
    M20;
#undef M
    default:
      throw too_many_ints();
    }
  }

  void move(lotsa_tuples&& other) {
    how_many_ints = other.how_many_ints;
    switch(how_many_ints) {
#define M(n) case n: \
      std::cout << "moving tuple_type<" #n ">\n"; \
      ::new (&tuples.t##n) tuple_type<n>(std::move(other.tuples.t##n)); \
      break
    M20;
#undef M
    default:
      throw too_many_ints();
    }
  }
};
#undef M20

int main() {
    std::vector<int> vec{31, 24};
    auto x = lotsa_tuples(vec.size());
    auto y = lotsa_tuples(12);
    x = y;
}
