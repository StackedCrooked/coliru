#include <iostream>
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

template<class Fn, class TupleArr>
struct needs_apply {
    template <class F=Fn>
    static auto test(int) ->
      decltype(std::declval<F>()(*std::declval<TupleArr>().begin()), std::false_type{});
    static auto test(...) -> std::true_type;
    using type = decltype(test(0));
};

template<class Fn, class TupleArr>
void tuple_array_map(Fn f, const TupleArr& arr, std::false_type)
{
    for (auto&& i : arr)
        static_cast<void>(f(i));
}

template<class Fn, class TupleArr>
void tuple_array_map(Fn f, const TupleArr& arr, std::true_type)
{
    tuple_array_map([&](const typename TupleArr::value_type& t) {
                return apply(f, t);
            }, arr, std::false_type{});
}

template<class Fn, class TupleArr>
void tuple_array_map(Fn&& f, TupleArr&& arr) {
    tuple_array_map(std::forward<Fn>(f), std::forward<TupleArr>(arr),
                    typename needs_apply<Fn,TupleArr>::type{});
}

int main()
{
    using T = std::tuple<double>;
    std::array<T, 5> tuples = {{
        T{1}, T{2}, T{3}, T{4}, T{5}
    }};

    // "apply" unpacks a tuple into arguments to a function
    apply(f1, tuples[0]);

    // this call produces an ambiguity one level down under clang
    tuple_array_map(f1, tuples);
    // this call directly produces an ambiguity under clang
    tuple_array_map(f2, tuples);
}
