// для MSVC
#pragma warning( disable : 4309 )
// для GCC
//g++ -std = c++14 -w main.cpp

#include <iostream>
#include <string>
#include <cstdint>
#include <typeinfo>
#include <type_traits>


namespace types
{
  template< uint8_t val >
  struct byte_
  {
    static const uint8_t value = val;
  };

  template< char val >
  struct char_
  {
    static const char value = val;
  };

  template< bool val >
  struct bool_
  {
    static const bool value = val;
  };

  template< size_t val >
  struct size_t_
  {
    static const size_t value = val;
  };

  template < char ... >
  struct string_t
  {
  };

  template < uint8_t ... >
  struct byte_vector_t
  {
  };

}


namespace utils
{
  template <char ... vals>
  void printn( const types::string_t<vals...> & )
  {
    for ( auto&& v : { vals... } ) std::cout << v;
    std::cout << std::endl;
  }

  template <typename Type, char ch = 0, uint8_t ... vals>
  void printn( const types::byte_vector_t<vals...> & )
  {
    const char delim [2] = { ch };
    for ( auto&& v : { vals... } ) std::cout << static_cast<Type>( v ) << delim;
    std::cout << std::endl;
  }

  void printn( const types::string_t<> & )
  {
    std::cout << '"' << '"' << std::endl;
  }

  void printn( const types::byte_vector_t<> & )
  {
    std::cout << '"' << '"' << std::endl;
  }

}


namespace algo
{
  template <typename Cont, size_t n>
  struct get_n;

  template <uint8_t x, uint8_t... xs>
  struct get_n<types::byte_vector_t<x, xs...>, 0>
  {
    using type = types::byte_<x>;
  };

  template <uint8_t x, uint8_t... xs, size_t n>
  struct get_n<types::byte_vector_t<x, xs...>, n>
  {
    static_assert( n <= sizeof...( xs ), "Out of Range" );
    using type = typename get_n< types::byte_vector_t<xs...>, n - 1 >::type;
  };


  template <typename Cont, size_t n, typename Val>
  struct set_n;

  template <typename Src, typename Dest, size_t n, typename Val>
  struct __set_n;

  template <uint8_t ... xs2, uint8_t val, size_t n>
  struct __set_n< types::byte_vector_t<>, types::byte_vector_t<xs2...>, n, types::byte_<val>>
  {
    using type = types::byte_vector_t<xs2...>;
  };

  template <uint8_t x, uint8_t ... xs, uint8_t ... xs2, uint8_t val>
  struct __set_n< types::byte_vector_t<x, xs...>, types::byte_vector_t<xs2...>, 0, types::byte_<val>>
  {
    using type = typename __set_n< types::byte_vector_t<xs...>, types::byte_vector_t<xs2..., val>, -1, types::byte_<val> >::type;
  };

  template <uint8_t x, uint8_t ... xs, uint8_t ... xs2, size_t n, uint8_t val>
  struct __set_n< types::byte_vector_t<x, xs...>, types::byte_vector_t<xs2...>, n, types::byte_<val>>
  {
    using type = typename __set_n< types::byte_vector_t<xs...>, types::byte_vector_t<xs2..., x>, n - 1, types::byte_<val> >::type;
  };


  template <uint8_t ... xs, size_t n, uint8_t val>
  struct set_n< types::byte_vector_t<xs...>, n, types::byte_<val>>
  {
    static_assert( sizeof...( xs ) > n, "Wrong index" );
    using type =
      std::enable_if_t
      < ( n < sizeof...( xs ) )
      , typename __set_n< types::byte_vector_t<xs...>, types::byte_vector_t<>, n, types::byte_<val> >::type
      >;
  };

  template <typename Cont, size_t n, uint8_t val>
  using set_n_t = typename set_n< Cont, n, types::byte_<val>>::type;

  template <typename Cont, size_t n>
  using get_n_t = typename get_n< Cont, n >::type;


  template <typename Case, typename Then >
  struct case_{};

  template <typename Then >
  struct default_{};

  template <typename Val, typename ... Cases>
  struct switch_
  {};

  template <typename Key, typename ... Cases, typename Type>
  struct switch_<Key, case_<Key, Type>, Cases...>
  {
    using type = Type;
  };

  template <typename Key, typename ... Cases, typename Type>
  struct switch_<Key, default_<Type>, Cases...>
  {
    using type = Type;
  };

  template <typename Key, typename Case, typename ... Cases>
  struct switch_<Key, Case, Cases...>
  {
    using type = typename switch_< Key, Cases... >::type;
  };

  template <typename Key, typename ... Cases>
  using switch_t = typename switch_< Key, Cases...>::type;

}


namespace brain_fuck
{
  template <typename Code, typename Data, typename Output, typename Index, typename Next>
  struct brain_fuck_t;

  template <uint8_t ... data, uint8_t ... output, size_t index>
  struct brain_fuck_t< types::string_t<>, types::byte_vector_t<data...>, types::byte_vector_t<output...>, types::size_t_<index>, types::bool_<true> >
  {
    using code_t  = types::string_t<>;
    using output_t = types::byte_vector_t<output...>;
    using data_t = types::byte_vector_t<data...>;

    using index_t = types::size_t_<index>;
    using current_val_t = algo::get_n_t<data_t, index>;

    using type = brain_fuck_t< code_t, data_t, output_t, index_t, types::bool_<true> >;
  };

  template <typename Code, uint8_t ... data, uint8_t ... output, size_t index >
  struct brain_fuck_t< Code, types::byte_vector_t<data...>, types::byte_vector_t<output...>, types::size_t_<index>, types::bool_<false> >
  {
    using code_t = Code;
    using output_t = types::byte_vector_t<output...>;
    using data_t = types::byte_vector_t<data...>;

    using index_t = types::size_t_<index>;
    using current_val_t = algo::get_n_t<data_t, index>;

    using type = brain_fuck_t< code_t, data_t, output_t, index_t, types::bool_<false> >;
  };

  template <typename Code, typename Data, typename Output, typename Index, typename Next>
  struct brain_fuck_helper_forward_t;

  template <typename Code, typename Data, typename Output, typename Index, typename Next>
  struct brain_fuck_helper_backward_t;
  
  template <char ch, char ...code, uint8_t ... data, uint8_t ... output, size_t index >
  struct brain_fuck_t< types::string_t<ch, code...>, types::byte_vector_t<data...>, types::byte_vector_t<output...>, types::size_t_<index>, types::bool_<true> >
  {
    using Next = types::bool_<true>;
    using code_t  = types::string_t< code...>;
    using data_t  = types::byte_vector_t<data...>;
    using output_t = types::byte_vector_t<output...>;

    using index_t = types::size_t_<index>;
    using key_t   = types::char_< ch >;
    using current_val_t = algo::get_n_t<data_t, index>;

    using next_t =
      algo::switch_t< key_t
                    , algo::case_< types::char_<'>'>, brain_fuck_t< code_t, data_t, output_t, types::size_t_<index + 1>, Next> > 
                    , algo::case_< types::char_<'<'>, brain_fuck_t< code_t, data_t, output_t, types::size_t_<index - 1>, Next> >
                    , algo::case_< types::char_<'+'>, brain_fuck_t< code_t, algo::set_n_t<data_t, index, current_val_t::value + 1>, output_t, index_t, Next> >
                    , algo::case_< types::char_<'-'>, brain_fuck_t< code_t, algo::set_n_t<data_t, index, current_val_t::value - 1>, output_t, index_t, Next> >
                    
                    , algo::case_< types::char_<'.'>, brain_fuck_t< code_t, data_t, types::byte_vector_t<output..., current_val_t::value >, index_t, Next> >

                    , algo::case_< types::char_<']'>, brain_fuck_t< code_t, data_t, output_t, index_t, types::bool_<false>> >
                    , algo::case_< types::char_<'['>, std::conditional_t< 
                                                                         current_val_t::value == 0
                                                                         , brain_fuck_helper_forward_t< code_t, data_t, output_t, index_t, Next>
                                                                         , brain_fuck_helper_backward_t< types::string_t< ch, code...>, data_t, output_t, index_t, Next>
                                                                         > >

                    , algo::default_< brain_fuck_t< code_t, data_t, output_t, index_t, Next> >
                    >;

    using type = typename next_t::type;

  };


  template <char ch, char ...code, typename Data, typename Output, typename Index, typename Next>
  struct brain_fuck_helper_backward_t<types::string_t< ch, code...>, Data, Output, Index, Next>
  {
    using code_t = types::string_t< ch, code...>;
    using subtype = typename brain_fuck_t< types::string_t< code...>, Data, Output, Index, Next>::type;
    using type = typename brain_fuck_t< code_t, typename subtype::data_t, typename subtype::output_t, typename subtype::index_t, Next>::type;
  };

  template <typename Code, typename Data, typename Output, typename Index, typename Next>
  struct brain_fuck_helper_forward_t
  {
    using subtype = typename brain_fuck_t< Code, Data, Output, Index, Next>::type;
    using type = typename brain_fuck_t< typename subtype::code_t, Data, Output, Index, Next>::type;
  };

}


int main()
{
  // ++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.
  // Hello World!
  using code = types::string_t < '+', '+', '+', '+', '+', '+', '+', '+', '[', '>', '+', '+', '+', '+'
                                , '[', '>', '+', '+', '>', '+', '+', '+', '>', '+', '+', '+', '>', '+'
                                , '<', '<', '<', '<', '-', ']', '>', '+', '>', '+', '>', '-', '>', '>'
                                , '+', '[', '<', ']', '<', '-', ']', '>', '>', '.', '>', '-', '-', '-'
                                , '.', '+', '+', '+', '+', '+', '+', '+', '.', '.', '+', '+', '+', '.'
                                , '>', '>', '.', '<', '-', '.', '<', '.', '+', '+', '+', '.', '-', '-'
                                , '-', '-', '-', '-', '.', '-', '-', '-', '-', '-', '-', '-', '-', '.'
                                , '>', '>', '+', '.', '>', '+', '+', '.'>;

  using data = types::byte_vector_t< 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>;
  using output = types::byte_vector_t<>;

  using index = types::size_t_<0>;
  using next = types::bool_<true>;

  using result = brain_fuck::brain_fuck_t< code, data, output, index, next >::type;

  utils::printn( code {} );
  utils::printn<int, ' '>( result::data_t {} );
  utils::printn<char>( result::output_t {} );

  return EXIT_SUCCESS;
}
