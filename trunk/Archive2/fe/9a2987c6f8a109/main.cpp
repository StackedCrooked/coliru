#include <tuple>
#include <array>
#include <utility>
#include <type_traits>

double f1(double x)
{
    return x * 2;
}

double f2(const std::tuple<double>& x)
{
    return std::get<0>(x) * 2;
}

template<std::size_t N>
struct apply_impl {
    template<class F, class Tuple, class... TParams>
    static auto apply(F&& fn, Tuple&& t, TParams&&... args)
      ->  decltype(
              apply_impl<N - 1>::apply(
                  std::forward<F>(fn), std::forward<Tuple>(t),
                  std::get<N - 1>(std::forward<Tuple>(t)),
                  std::forward<TParams>(args)...
          ))
    {
        return apply_impl<N - 1>::apply(
                std::forward<F>(fn), std::forward<Tuple>(t),
                std::get<N - 1>(std::forward<Tuple>(t)),
                std::forward<TParams>(args)...
                );
    }
};

template<>
struct apply_impl<0> {
    template<class F, class Tuple, class... TParams>
    static auto apply(F&& fn, Tuple&&, TParams&&... args)
      -> decltype(std::forward<F>(fn)(std::forward<TParams>(args)...))
    {
        return std::forward<F>(fn)(std::forward<TParams>(args)...);
    }
};

template<class F, class Tuple>
auto apply(F&& fn, Tuple&& t)
  -> decltype(apply_impl<
          std::tuple_size<typename std::decay<Tuple>::type>::value
        >::apply(std::forward<F>(fn), std::forward<Tuple>(t)))
{
    return apply_impl<
        std::tuple_size<typename std::decay<Tuple>::type>::value
      >::apply(std::forward<F>(fn), std::forward<Tuple>(t));
}

template<class Fn, class TupleArr,
    class = decltype(std::declval<Fn>()(
                std::declval<typename TupleArr::value_type>()))>
void tuple_array_map(Fn f, const TupleArr& arr)
{
    for (auto i = 0; i < arr.size(); ++i)
        static_cast<void>(f(arr[i]));
}

template<class Fn, class TupleArr,
    class = decltype(apply(std::declval<Fn>(),
                std::declval<typename TupleArr::value_type>())),
    class = void>
void tuple_array_map(Fn f, const TupleArr& arr)
{
    tuple_array_map([&](const typename TupleArr::value_type& t) {
                return apply(f, t);
            }, arr);
}

int main()
{
    std::array<std::tuple<double>, 5> tuples = {
        std::make_tuple(1),
        std::make_tuple(2),
        std::make_tuple(3),
        std::make_tuple(4),
        std::make_tuple(5)
    };

    // "apply" unpacks a tuple into arguments to a function
    apply(f1, tuples[0]);

    // this call produces an ambiguity one level down under clang
    tuple_array_map(f1, tuples);
    // this call directly produces an ambiguity under clang
    tuple_array_map(f2, tuples);
}
