
#include <boost/preprocessor.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/if.hpp>

#include <iostream>
#include <cstring>
#include <exception>
#include <stdexcept>

/* It was asked here
 * http://stackoverflow.com/questions/20965003/how-to-concatenate-a-const-char-in-compile-time/20973438#20973438
 */
 
#define NUM_CHARS 32
#define CHARS_GEN(count,i,data) data ## i
#define GEN_CHARSP(N) BOOST_PP_ENUM(N,CHARS_GEN,char C)
#define GEN_CHARS(N) BOOST_PP_ENUM(N,CHARS_GEN, C)

/*Jarod42 classes*/
template<char...Cs> struct seq
{
    typedef const char (&arr_type)[sizeof...(Cs) + 1];
    static constexpr arr_type c_str() { return str; }
    static constexpr char str[sizeof...(Cs) + 1] = {Cs..., '\0'};
};

template<char...Cs>
constexpr char seq<Cs...>::str[sizeof...(Cs) + 1];


template<typename T, typename ... Ts>
struct concat_seq;

template<char...Cs>
struct concat_seq<seq<Cs...>> : seq<Cs...> {
    typedef seq<Cs...> type;
};

template<char...Cs1, char...Cs2>
struct concat_seq<seq<Cs1...>, seq<Cs2...>> : seq<Cs1..., Cs2...> {
    typedef seq<Cs1...,Cs2...> type;
};

template<char...Cs1, char...Cs2, typename ... Ts>
struct concat_seq<seq<Cs1...>, seq<Cs2...>, Ts...> :
    concat_seq<seq<Cs1..., Cs2...>, Ts...> {};

template<typename ... Ts>
struct concat_seq<std::tuple<Ts...>> : concat_seq<Ts...> {};

/*Abrahams function*/
template <int N>
constexpr char at(char const(&s)[N], int i)
{
  return i >= N ? '\0' : s[i];
}

#define AT(count,i,s) at(s,i)

namespace mpl = boost::mpl;

/*My modification, but abraham's way */
template<size_t N>
constexpr size_t str_size(const char (&a)[N]){
    return N-1;
}
#define PRE_MACRO(z,i,s) \
     typename                                                           \
        mpl::if_<                                                       \
        typename mpl::equal_to<mpl::int_<i>,mpl::int_<N> >::type,       \
                 seq<GEN_CHARS(i)>,
#define POST_MACRO(z,i,s) >::type

/*TODO: incorect count of paramenters N is 31, params is 32*/
template <size_t N, GEN_CHARSP(NUM_CHARS)> 
struct create_sequence  {   
    typedef 
    BOOST_PP_REPEAT(NUM_CHARS,PRE_MACRO,"")
    void
    BOOST_PP_REPEAT(NUM_CHARS,POST_MACRO,"")
    type;
};

#define _S(s) create_sequence<str_size(s),BOOST_PP_ENUM(NUM_CHARS,AT,s)>::type
    
int main()
{
      typedef _S("first_string_sequence ") sq1;
      typedef _S("second_string_sequence ") sq2;
      typedef _S("И такие строки ") sq3;   
      
      std::cout << sq1::c_str() << std::endl;
      std::cout << sq2::c_str() << std::endl;
      std::cout << sq3::c_str() << std::endl;
      
      typedef concat_seq<std::tuple< sq1, sq2 >>::type str1;
      typedef concat_seq<std::tuple< str1, sq3 >>::type str2;
    

      std::cout << str1::c_str() << std::endl;
      std::cout << str2::c_str() << std::endl;


    return 0;
}