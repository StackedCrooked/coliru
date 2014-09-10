#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <cstring>

    namespace string_builder {
      template<class String, class=std::enable_if_t< std::is_same< String, std::string >::value >>
      std::size_t get_size( String const& s ) { return s.size(); }
      std::size_t get_size( const char* s ) { return std::strlen(s); }
      template<std::size_t N>
      constexpr std::size_t get_size( const char(&)[N] ) { return N; }
      template<class Indexes, class...Ss>
      struct op;
      struct tuple_tag {};
      template<size_t... Is, class... Ss>
      struct op<std::integer_sequence<size_t, Is...>, Ss...> {
        op() = default;
        op(op const&) = delete;
        op(op&&) = default;
        std::tuple<Ss...> data;
        template<class... Tuples>
        op( tuple_tag, Tuples&&... ts ): data( std::tuple_cat( std::forward<Tuples>(ts)... ) ) {}
        std::size_t size() const {
          std::size_t retval = 0;
          int unused[] = {((retval+=get_size(std::get<Is>(data))), 0)..., 0};
          (void)unused;
          return retval;
        }
        operator std::string() && {
          std::string retval;
          retval.reserve( size()+1 );
          int unused[] = {((retval+=std::forward<Ss>(std::get<Is>(data))), 0)..., 0};
          (void)unused;
          return retval;
        }
        template<class S0>
        op<std::integer_sequence<size_t, Is..., sizeof...(Is)>, Ss..., S0>
        operator+(S0&&s0)&& {
          return { tuple_tag{}, std::move(data), std::forward_as_tuple( std::forward<S0>(s0) ) };
        }
        auto operator()()&& {return std::move(*this);}
        template<class T0, class...Ts>
        auto operator()(T0&&t0, Ts&&... ts)&&{
          return (std::move(*this)+std::forward<T0>(t0))(std::forward<Ts>(ts)...);
        }
      };
    }
    string_builder::op< std::integer_sequence<std::size_t> >
    string_build() { return {}; }
    template<class... Strings>
    auto
    string_build(Strings&&...strings) { return string_build()(std::forward<Strings>(strings)...); }

    std::string Concatenate(const std::string& s1,
                            const std::string& s2,
                            const std::string& s3,
                            const std::string& s4,
                            const std::string& s5)
    {
      return string_build() + s1 + s2 + s3 + s4 + s5;
    }

    template<class... Strings>
    std::string Concatenate(Strings&&...strings)
    {
      return string_build(std::forward<Strings>(strings)...);
    }

int main()
{
    std::cout << Concatenate("Hello", " World!").c_str() << "\n";
}
