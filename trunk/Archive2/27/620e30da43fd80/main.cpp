#include <iostream>
#include <utility>
#include <tuple>

    template<unsigned... Is> struct indexes {typedef indexes<Is...> type;};
    template<unsigned Max, unsigned... Is> struct make_indexes:make_indexes<Max-1, Max-1, Is...> {};
    template<unsigned... Is> struct make_indexes<0, Is...>:indexes<Is...> {};

    template<int I, typename... Args>
    struct inner_helper {
      std::tuple<Args...> args;
      template<typename T, unsigned... Is>
      T construct(indexes<Is...>) const && {
        return { std::forward<Args>(std::get<Is>(args))... };
      }
      template<typename T>
      T construct() const && {
        return std::move(*this).template construct<T>( make_indexes<sizeof...(Args)>() );
      }
    };
    template<int I, typename... Args>
    inner_helper<I, Args...> inner( Args&&... args ) {
      return {std::forward<Args>(args)...};
    }
    template<class T>
    struct testclass
    {
      template<int I>
      class inner {};
      template<int I>
      void f(inner<I> ) {}
      template<int I, typename... Args>
      void f(inner_helper<I, Args...> h) {
        return f( std::move(h).template construct<inner<I>>() );
      }
    };

    int main()
    {
      testclass<bool> test;
      test.f(inner<3>()); // l. 13
      return 0;
    }
