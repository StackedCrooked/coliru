#include <iterator>

template <int i> struct rank : rank<i+1> {};
template <> struct rank<10> {};
constexpr rank<0> call_ranked{};

#define AUTO_RETURN(...) -> decltype(__VA_ARGS__) {return (__VA_ARGS__);}

namespace detail {
    
    template <typename T,
              typename = typename std::enable_if<std::is_array<typename std::remove_reference<T>::type>{}>::type>
    auto adl_begin( rank<0>, T&& t )
      AUTO_RETURN(t + 0)
    template <typename T,
              typename = typename std::enable_if<std::is_array<typename std::remove_reference<T>::type>{}>::type>
    auto adl_end  ( rank<0>, T&& t )
      AUTO_RETURN(t + std::extent<typename std::remove_reference<T>::type>{})
      
    template <typename T>
    auto adl_begin( rank<1>, T&& t )
      AUTO_RETURN(std::forward<T>(t).begin())
    template <typename T>
    auto adl_end( rank<1>, T&& t )
      AUTO_RETURN(std::forward<T>(t).end  ())
      
    template <typename T>
    auto adl_begin( rank<2>, T&& t )
      AUTO_RETURN(begin(std::forward<T>(t)))
    template <typename T>
    auto adl_end  ( rank<2>, T&& t )
      AUTO_RETURN(end  (std::forward<T>(t)))
}

template <typename T>
auto adl_begin(T&& t) AUTO_RETURN(detail::adl_begin(call_ranked, std::forward<T>(t)))
template <typename T>
auto adl_end  (T&& t) AUTO_RETURN(detail::adl_end  (call_ranked, std::forward<T>(t)))

/// TEST:

namespace A {struct C{}; int* begin(C) {return 0;} int* end(C) {return 0;}}

int main()
{
    A::C c, arr[10];
    auto begin = adl_begin(c), 
         end   = adl_end(c);
    auto begin_arr = adl_begin(arr), 
         end_arr   = adl_end(arr);
    (void)begin, (void)end;(void)begin_arr, (void)end_arr;
}