#include <tuple>        // std::tuple, std::get
#include <utility>      // std::integer_sequence
#include <memory>       // std::unique_ptr

template<class T, class... Args>
struct LazyConstruct {
   // accept any number of arguments, 
   // which would later be used to construct T
   template<class... U>
   LazyConstruct(U&&... u)
   : args(std::make_tuple(std::forward<U>(u)...))
   {
   }

   T& get() {
      if(!data) data = create(std::index_sequence_for<Args...>());
      return *data;
   }

   template<std::size_t... I>
   std::unique_ptr<T> create(std::integer_sequence<std::size_t, I...>)
   {
      return std::unique_ptr<T>{new T(std::get<I>(args)...)};
   }

private:
   std::tuple<typename std::decay<Args>::type...> args;
   std::unique_ptr<T> data;
};

template<class T, class... Args>
LazyConstruct<T, Args...> make_LazyConstruct(Args&&... args)
{
    return LazyConstruct<T, Args...>{std::forward<Args>(args)...};
}

#include <iostream>

void say( char const* const s ) { std::cout << s << std::endl; }

struct Arg
{
    Arg() { say( "Arg::<default>" ); }
    Arg( Arg const& ) { say( "Arg::<copy>" ); }
    Arg( Arg&& ) { say( "Arg::<move>" ); }
};

struct Foo
{
    Foo( Arg const& ) {}
};

auto main() -> int
{
    Arg const a;
    auto lc1 = make_LazyConstruct< Foo >( a );
    say( "" );
    auto lc2 = make_LazyConstruct< Foo >( Arg() );
    say( "" );
    LazyConstruct<Foo, Arg const&> lc3( a );
}
