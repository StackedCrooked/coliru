#include <type_traits>
#include <iostream>
#include <tuple>
#include <string>

template<typename Tuple>
struct Base {
  typedef Tuple typle_t;

  template<typename Ret>
  Ret const& get_current (Tuple const& t) {
    return *reinterpret_cast<Ret*> (get (t));
  }

  virtual Base       * next () = 0;
  virtual void const * get (Tuple const&) = 0;
};

template<int N, int Max, typename T>
struct hack : Base<T> {

  void const* get (T const& x) override { return &std::get<N> (x); }
  Base<T> * next () override { return new hack<N+1, Max, T>; }
};

template<int N, typename T> struct hack<N,N, T> : Base<T> {
  Base<T> * next () override { return nullptr; }
  void const * get  (T const&) override { return nullptr; }
};

template<typename Tuple>
struct Wrap {
  Wrap ()
    : itr (new hack<0, std::tuple_size<Tuple>::value, Tuple>)
  {}

  template<typename Ret>
  Ret const& get (Tuple const& t) {
    Ret const& ret = *reinterpret_cast<Ret const*> (itr->get (t));

    itr = itr->next ();

    return ret;
  }

  Base<Tuple> * itr; 
};

template<typename F, typename... Args>
void call (F f, std::tuple<Args...> const& t)
{
  Wrap<std::tuple<Args...>> itr;

  f ( (itr.template get<Args> (t)) ...); // UB
}

void
func (int a, std::string b) {
  std::cout << a << ", " << b << std::endl;
}

int
main (int argc, char *argv[])
{
  call (func, std::make_tuple (1,"hello world"));
}