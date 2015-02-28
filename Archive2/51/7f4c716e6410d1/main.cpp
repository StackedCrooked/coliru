#include <type_traits>
#include <cassert>
#include <iostream>

template<class...>struct types{using type=types;};

template<class D, int i, class T, bool = std::is_empty<T>::value>
struct tuple_leaf
{
  tuple_leaf(T x) : val(x) {}

  T& get() { return val; }

  T val;
};


template<class D, int i, class T>
struct tuple_leaf<D, i,T,true> : private T
{
  tuple_leaf(T x) : T(x) {}

  T& get() { return *this; }
};


template<int i, class T1, class T2>
struct type_at
{
  using type = T1;
};


template<class T1, class T2>
struct type_at<1,T1,T2>
{
  using type = T2;
};


template<class T1, class T2>
struct tuple_base : tuple_leaf<types<T1,T2>, 0,T1>, tuple_leaf<types<T1,T2>, 1,T2>
{
  tuple_base(T1 a, T2 b) : tuple_leaf<types<T1,T2>, 0,T1>(a), tuple_leaf<types<T1,T2>, 1,T2>(b) {}

  template<int i>
  tuple_leaf<types<T1,T2>, i,typename type_at<i,T1,T2>::type> get_leaf()
  {
    // XXX how to disambiguate this conversion?
    return *this;
  }
};


// XXX deriving from tuple_base rather than
//     making tuple_base a member is the root of the issue
template<class T1, class T2>
struct my_tuple : tuple_base<T1,T2>
{
  my_tuple(T1 a, T2 b) : tuple_base<T1,T2>(a, b) {}
};

template<int i, class T1, class T2>
typename type_at<i,T1,T2>::type& get(my_tuple<T1,T2>& t)
{
  return (t.template get_leaf<i>()).get();
}

template<class T1,class T2>
my_tuple<T1,T2> make_tuple(T1 a, T2 b)
{
  return my_tuple<T1,T2>(a,b);
}

struct empty {};

int main()
{
  using tuple1 = my_tuple<empty, empty>;
  static_assert((std::is_empty<tuple1>::value), "tuple1 not empty");
  static_assert(sizeof(tuple1)==1, "tuple1 sizeof not 1");
  using tuple2 = my_tuple<empty, tuple1>;
  static_assert((std::is_empty<tuple2>::value), "tuple2 not empty");
  static_assert(sizeof(tuple2)==1, "tuple2 sizeof not 1");
  auto tuple = make_tuple(empty(), make_tuple(empty(),empty()));

  static_assert((std::is_empty<decltype(tuple)>::value), "not empty");
  std::cout << sizeof(tuple) << std::endl;
  assert(sizeof(tuple) == sizeof(empty));

  get<0>(tuple);

  return 0;
}