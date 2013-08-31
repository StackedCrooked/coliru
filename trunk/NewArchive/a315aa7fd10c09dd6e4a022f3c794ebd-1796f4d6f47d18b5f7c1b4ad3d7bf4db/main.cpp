
#include <cstdint>
#include <climits>
#include <cstddef>

#include <array>
#include <tuple>
#include <functional>
#include <type_traits>
#include <stdexcept>
#include <iostream>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/at.hpp>


namespace detail {

  template<size_t I, size_t END, typename Vector>
  struct functor
  {
    typedef typename boost::mpl::at_c<Vector, I>::type Element;
    template<typename...Args>
    inline auto operator()(size_t which, Args&&...args) const -> 
   decltype( (I == which) ? Element{}(std::forward<Args>(args)...)
             :              functor<I+1, END, Vector>{}(which, std::forward<Args>(args)...)  )
    {
      return (I == which) ? Element{}(std::forward<Args>(args)...)
             :              functor<I+1, END, Vector>{}(which, std::forward<Args>(args)...);
    }
  };

  template<size_t END, typename Vector>
  struct functor<END, END, Vector>
  {
    template<typename...Args>
    inline int operator()(size_t which, Args&&...) const 
    {
      throw std::runtime_error("Failed");
      return 0;
    }
  };
}

template<typename...Types>
class function_wrapper
{
public:
  typedef boost::mpl::vector<Types...> type_list_;
  std::size_t index_;
public:
  constexpr function_wrapper() : index_(-1) {}
  template<typename T> constexpr function_wrapper(T&&t) : 
    index_(boost::mpl::distance<
                         typename boost::mpl::begin<type_list_>::type, 
                         typename boost::mpl::find<type_list_, T>::type
                        >::value) {}

  template<typename T> inline function_wrapper& operator=(T&&t)
  {
    index_ = boost::mpl::distance<
                         typename boost::mpl::begin<type_list_>::type, 
                         typename boost::mpl::find<type_list_, T>::type
                        >::value;
    return *this;
  }

  template<typename...Args>
  inline auto operator()(Args&&...args) const -> 
    decltype( detail::functor<0, sizeof...(Types), type_list_>{}(index_, std::forward<Args>(args)...) ) 
  {
    return detail::functor<0, sizeof...(Types), type_list_>{}(index_, std::forward<Args>(args)...);
  }
};

template<typename...Args>
inline function_wrapper<Args...> make_wrapper(Args&&...args)
{
    return function_wrapper<Args...>();
}

struct f1
{
    template<typename T1, typename T2>
    inline auto operator()(T1 a, T2 b) const -> decltype(a+b)
    {
        return a + b;
    }
};

struct f2
{
    template<typename T1, typename T2>
    inline auto operator()(T1 a, T2 b) const -> decltype(a*b)
    {
        return a * b;
    }
};

struct f3
{
    template<typename T1, typename T2>
    inline auto operator()(T1 a, T2 b) const -> decltype(a%b)
    {
        return a % b;
    }
};

int main(int argc, char **argv)
{
  using namespace std;
  
  function_wrapper<f1, f2, f3> func;

  size_t choice = atoi(argv[1]);
  switch(choice)
  {
  case 0:
    func = f1();
    break;
  case 1:
    func = f2();
    break;
  case 2:
    func = f3();
    break;
  }

  cout << func(3, 5) << endl;

  return 0;
}


