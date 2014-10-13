namespace std {
typedef int size_t;
template <typename _Tp, _Tp> struct integral_constant {
  typedef _Tp value_type;
  typedef integral_constant type;
  constexpr operator value_type() { return 0; }
};
template <typename _Tp> _Tp &&declval();
template <typename _Tp> struct remove_const {
  typedef _Tp type;
};
template <typename _Tp> struct remove_volatile {
  typedef _Tp type;
};
template <typename _Tp> struct remove_cv {
  typedef typename remove_const<typename remove_volatile<_Tp>::type>::type type;
};
template <typename _Tp> struct remove_reference {
  typedef _Tp type;
};
template <typename _Tp> struct remove_reference<_Tp &> {
  typedef _Tp type;
};
template <typename _Tp> struct __decay_and_strip;
template <typename _Tp>
constexpr _Tp &&forward(typename std::remove_reference<_Tp>::type &__t) {
  return static_cast<_Tp &&>(__t);
}
template <class _Tp> class tuple_size;
template <std::size_t, class _Tp> class tuple_element;
template <size_t... _Indexes> struct _Index_tuple;
template <size_t _Num> struct _Build_index_tuple;
template <> struct _Build_index_tuple<0> {
  typedef _Index_tuple<> __type;
};
template <typename _Tp, _Tp... _Idx> struct integer_sequence {};
template <typename _Tp, _Tp _Num,
          typename = typename _Build_index_tuple<_Num>::__type>
struct _Make_integer_sequence;
template <typename _Tp, _Tp _Num, size_t... _Idx>
struct _Make_integer_sequence<_Tp, _Num, _Index_tuple<_Idx...> > {
  typedef integer_sequence<_Tp, static_cast<_Tp>(_Idx)...> __type;
};
template <std::size_t, typename... _Elements> struct _Tuple_impl;
template <std::size_t _Idx> struct _Tuple_impl<_Idx> {};
template <typename... _Elements> class tuple : _Tuple_impl<0, _Elements...> {};
template <typename... _Elements>
struct tuple_size<tuple<
    _Elements...> > : integral_constant<std::size_t, sizeof...(_Elements)> {};
template <typename... _Elements>
tuple<typename __decay_and_strip<_Elements>::__type...>
make_tuple(_Elements &&...);
template <typename...> struct void_ {
  typedef void type;
};
template <typename Num> constexpr Num min(Num &&num) {
  return std::forward<Num>(num);
}
template <typename... Concepts> struct requires;
namespace {
template <typename, typename = void> struct tuple_size;
template <typename Tuple>
struct tuple_size<
    Tuple, typename void_<typename std::tuple_size<typename std::remove_cv<
               typename std::remove_reference<Tuple>::type>::type>::type>::
               type> : std::
                           tuple_size<typename remove_cv<
                               typename std::remove_reference<
                                   Tuple>::type>::type>::type {};
namespace concepts {
template <typename Type> struct Tuple;
template <typename, typename... Args> struct Invokable;
namespace annex {
template <typename Derived> struct perfect_functor;
template <typename Functor>
struct uncurry_type : perfect_functor<uncurry_type<Functor> > {};
template <typename Functor> uncurry_type<Functor> uncurry(Functor &&);
namespace result_of {
template <typename Functor, typename... Tuple>
using uncurry =
    decltype(annex::uncurry(std::declval<Functor>, std::declval<Tuple>...));
namespace tuples {
namespace result_of {
using namespace annex::result_of;
namespace detail {
template <int Index, typename... Tuples,
          typename requires<concepts::Tuple<Tuples>...>::type...>
std::tuple<typename std::tuple_element<Index, Tuples>::type...>
slice(Tuples &&...);
namespace result_of {
using namespace tuples::result_of;
template <int Index, typename... Tuples>
using slice = decltype(detail::slice<Index>);
}
template <typename Functor, typename Tuple, typename... Tuples,
          int... ElementIndices,
          typename requires<
              concepts::Tuple<Tuple>, concepts::Tuple<Tuples>...,
              concepts::Invokable<result_of::uncurry<Functor &>,
                                  result_of::slice<ElementIndices, Tuples...> >,
              concepts::Invokable<
                  result_of::uncurry<Functor &>,
                  result_of::slice<ElementIndices, Tuples...> >...>::type...>
std::tuple<result_of::uncurry<Functor &,
                              result_of::slice<ElementIndices, Tuples...> >...>
zip_with(std::integer_sequence<int, ElementIndices...>, Functor &&, Tuple &&,
         Tuples &&...);
namespace result_of {
template <typename Functor, typename... Tuples>
using zip_with =
    decltype(detail::zip_with(typename _Make_integer_sequence<
                                  int, min(tuple_size<Tuples>()...)>::__type{},
                              std::declval<Functor>, std::declval<Tuples>...));
template <typename Functor, typename... Tuples>
using apply = zip_with<Functor, Tuples...>;
}
template <typename Functor, typename... Tuples>
result_of::apply<Functor, Tuples...> apply(Functor &&, Tuples &&...);
namespace operators {
struct addressof {};
int main() {
  auto tuple = std::make_tuple();
  apply(operators::addressof{}, tuple)