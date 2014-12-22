#include <cstddef>
#include <utility>
#include <type_traits>
template<bool...> struct foo {};

template <std::size_t N>
struct matrix
{
  const bool data_[N*N];

  template<typename... Values>
  constexpr matrix(Values... values) noexcept
    : data_{static_cast<bool>(values)...}
  {}

  constexpr bool operator [](std::size_t index) const noexcept
  {
    return data_[index];
  }
};

extern constexpr matrix<2> mat(true, false, true, false);

template<std::size_t N, const matrix<N> &Mat, class> struct ty1_helper;
template<std::size_t N, const matrix<N> &Mat, std::size_t... Is> struct ty1_helper<N, Mat, std::index_sequence<Is...>> { using type = foo<Mat[Is]...>; };

template<std::size_t N, const matrix<N> &Mat>
using ty1 = typename ty1_helper<N, Mat, std::make_index_sequence<N*N>>::type;

int main(){
    static_assert(std::is_same<ty1<2, mat>, foo<true, false, true, false>>::value, "Oops");
}