    #include <utility>
    #include <type_traits>
    
    template<bool b>
    struct static_if_t {
      static_if_t( static_if_t const& ) = default;
      static_if_t() = default;
      static_if_t( static_if_t<b>(*)(std::integral_constant<bool,b>) ) {}
    };

    template<bool dead>
    struct static_if_branch {};

    template<bool b>
    struct static_else_if_t {
      static_else_if_t( static_else_if_t const& ) = default;
      static_else_if_t() = default;
      static_else_if_t( static_else_if_t<b>(*)(std::integral_constant<bool,b>) ) {}
    };
    
    template<bool b>
    static_if_t<b> static_if(std::integral_constant<bool,b> unused=std::integral_constant<bool,b>()) {return {};}
    template<bool b>
    static_else_if_t<b> static_else_if(std::integral_constant<bool,b> unused=std::integral_constant<bool,b>()) {return {};}
    
    static auto static_else = static_else_if<true>;
    
    #include <iostream>
    
    template<typename Lambda, typename=typename std::enable_if< std::is_same< decltype(std::declval<Lambda&&>()()), decltype(std::declval<Lambda&&>()()) >::value >::type>
    static_if_branch<true> operator*( static_if_t<true>, Lambda&& closure )
    {
      std::forward<Lambda>(closure)();
      return {};
    }
    template<typename Lambda, typename=typename std::enable_if< std::is_same< decltype(std::declval<Lambda&&>()()), decltype(std::declval<Lambda&&>()()) >::value >::type>
    static_if_branch<false> operator*( static_if_t<false>, Lambda&& /*closure*/ )
    {
      return {};
    }
    
    template<typename Unused>
    static_if_branch<true> operator*( static_if_branch<true>, Unused&& ) {
      return {};
    }

    static_if_t< true > operator*( static_if_branch<false>, static_else_if_t<true> ) {
      return {};
    }
    static_if_t< false > operator*( static_if_branch<false>, static_else_if_t<false> ) {
      return {};
    }
    
    
    int main() {
      static_if<true>* [&]{
        std::cout << "hello\n";
      } *static_else* [&]{
        std::cout << "doom\n";
      };
    
      static_if<false>* [&]{
        std::cout << "doom the\n";
      } *static_else* [&]{
        std::cout << "world\n";
      };
    
      static_if<false>* [&]{
        std::cout << "fello\n";
      } *static_else_if<false>* [&]{
        std::cout << "yellow\n";
      } *static_else_if<false>* [&]{
        std::cout << "hehe\n";
      };
      
      static_if( std::is_same<int, int>() )*[&]{
        std::cout << "int is int\n";
      };
      static_if( std::is_same<double, double>() )*[&]{
        std::cout << "double is double\n";
      } *static_else_if( std::is_same<int, double>() )*[&]{
        std::cout << "int is double\n";
      } *static_else* [&]{
        std::cout << "sky is not blue\n";
      };
    }
