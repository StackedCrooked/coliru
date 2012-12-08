#include <iterator>
#include <type_traits>

template<unsigned... Is> struct seq{ using type = seq; };
template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class T> using Alias = T;
template<class T> using Invoke = typename T::type;
template<class T> using Strip = Invoke<std::remove_cv<Invoke<std::remove_reference<T>>>>;
template<class It> using IterCat = typename std::iterator_traits<It>::iterator_category;
template<class C, class T> using EnableIf = Invoke<std::enable_if<C::value, T>>;

namespace detail{
template<class T, class Seq> struct expand_invokable_;

template<class T, unsigned... Is>
struct expand_invokable_<T, seq<Is...>>{
  template<class F>
  static auto test(int) -> decltype(std::declval<F>()((void(Is), std::declval<T>())...), std::true_type{});
  template<class>
  static auto test(long) -> std::false_type;
};
} // detail::

template<class F, unsigned N, class T>
struct expand_invokable
  : decltype(detail::expand_invokable_<T, Invoke<gen_seq<N>>>::template test<F>(0)){};
  
template<class F, unsigned N, class T>
using ExpandInvokable = expand_invokable<F, N, T>;

template<class T> struct type{};

template<class T>
struct volatile_storage{
    T&& value;
    T&& get(){ return std::forward<T>(value); }
};

template<class T>
volatile_storage<T> vstore(T&& v){ return {std::forward<T>(v)}; }

template<class F, class T, unsigned N, unsigned... Is>
auto invoke_2(F f, volatile_storage<T> (&&x)[N], seq<Is...>)
  -> decltype(f((void(Is), std::declval<T>())...))
{
    return f(x[Is].get()...);
}

template<class F, class Args, unsigned... Is, class T>
auto invoke_1(F f, Args& cont, seq<Is...> s, std::input_iterator_tag, type<T>)
  -> decltype(f((void(Is), std::declval<T>())...))
{
    auto it = cont.begin();
    return invoke_2(f, Alias<volatile_storage<T>[]>{(void(Is), vstore(*it++))...}, s);
}

template<class F, class Args, unsigned... Is, class T>
auto invoke_1(F f, Args& cont, seq<Is...>, std::input_iterator_tag, type<T&>)
  -> decltype(f((void(Is), std::declval<T&>())...))
{
  auto it = cont.begin();
  T* x[]{(void(Is), &*it++)...};
  return f(*x[Is]...);
}

template<class F, class Args, unsigned... Is, class T>
auto invoke_1(F f, Args& cont, seq<Is...>, std::forward_iterator_tag, type<T>)
  -> decltype(f((void(Is), *cont.begin())...))
{
  auto it = cont.begin();
  decltype(it) x[]{(void(Is), ++it)...};
  return f(*x[Is]...);
}

template<class F, unsigned ArgC, class T>
struct invokable_assert{
    static_assert(ExpandInvokable<F, ArgC, T>::value, "Can't call F with ArgC arguments of type T");
    using type = int;
};

template<class F, unsigned ArgC, class T>
using InvokableAssert = Invoke<invokable_assert<F, ArgC, T>>;

template<unsigned ArgC, class F, class Args, InvokableAssert<F, ArgC, decltype(*std::declval<Args&>().begin())> = 0>
auto invoke(F f, Args& cont)
  -> decltype(invoke_1(f, cont, gen_seq<ArgC>{}, IterCat<decltype(cont.begin())>{}, type<decltype(*cont.begin())>{}))
{
  return invoke_1(f, cont, gen_seq<ArgC>{}, IterCat<decltype(cont.begin())>{}, type<decltype(*cont.begin())>{});
}

#include <iostream>
#include <vector>
#include <sstream>
#include <boost/range/istream_range.hpp>

void f(int, int, int, int){ std::cout << "f(int...) called\n"; }
void g(bool&, bool&, bool&, bool&){ std::cout << "g(bool...) called\n"; }

struct X{
  void operator()(int, int, int){}
};

class proxy_iter
{
private:
  typedef proxy_iter self;
public:
  typedef std::input_iterator_tag iterator_category;
  typedef bool value_type;
  struct reference {
    operator const value_type&() const { static bool const b = true; return b; }
  };
  typedef const value_type* pointer;
  typedef std::ptrdiff_t difference_type;
  self& operator=(const self&) { return *this;  }
  bool operator==(const self&) const { return false; }
  bool operator!=(const self&) const { return true; }
  reference operator*() const { return reference(); }
  self& operator++() { return *this; }
  self operator++(int) { return *this; }
};

int main(){
    std::vector<int> args1{1,2,3,4};
    invoke<4>(f, args1); // forward_iterator_tag
    std::vector<bool> args2{true, false, true, false};
    invoke<4>(f, args2);
    std::stringstream ss("1 2 3 4");
    auto args3 = boost::istream_range<int>(ss);
    invoke<4>(f, args3); // input_iterator_tag, T&
    auto args4 = boost::make_iterator_range(proxy_iter(), proxy_iter());
    invoke<4>(f, args4); // input_iterator_tag, T
}