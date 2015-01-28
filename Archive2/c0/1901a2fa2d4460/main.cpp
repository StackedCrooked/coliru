#include <iostream>
#include <utility>
#include <tuple>

template <class T> struct identity {using type = T;};

template <typename, std::size_t, typename, typename=void>
struct interlace;

struct next_tag;

template <typename... result, std::size_t index, 
          typename pack, typename... packs>
struct interlace<std::tuple<result...>, index, std::tuple<pack, packs...>,
                 std::enable_if_t<!std::is_same<pack, next_tag>{}>> :
    interlace<std::tuple<result..., std::tuple_element_t<index, pack>>,
              index, std::tuple<packs..., pack>> {};

template <typename... result, std::size_t index,
          typename pack, typename... packs>
struct interlace<std::tuple<result...>, index, std::tuple<next_tag, pack, packs...>,
                 std::enable_if_t<(index+1 < std::tuple_size<pack>::value)>> :
    interlace<std::tuple<result...>, index+1, std::tuple<packs..., next_tag>> {};

template <typename... result, std::size_t index,
          typename pack, typename... packs>
struct interlace<std::tuple<result...>, index, std::tuple<next_tag, pack, packs...>,
                 std::enable_if_t<index+1 == std::tuple_size<pack>::value>> :
    identity<std::tuple<result...>> {};

template <typename T> void print () {std::cout << __PRETTY_FUNCTION__;}

int main()
{
    print<interlace<std::tuple<>, 0,
                    std::tuple<std::tuple<int>, std::tuple<float>, std::tuple<double>, next_tag>
                   >::type
         >();
}