#include <type_traits>
#include <cassert>
#include <cstddef>

// define something like std::index_sequence
template<size_t... Indices>
struct index_sequence {};

// compute the exclusive scan of IndexSequence
// initializing the first value in the result sequence to Init
template<typename Current, size_t Next, class IndexSequence>
struct exclusive_scan_index_sequence_impl
{
    using type = Current;
};

template<size_t... Current, size_t Next, size_t First, size_t... Indices>
struct exclusive_scan_index_sequence_impl<index_sequence<Current...>,Next,index_sequence<First,Indices...>>
    : exclusive_scan_index_sequence_impl<index_sequence<Current...,Next>,Next+First,index_sequence<Indices...>>
{
};

template<size_t Init, class IndexSequence>
using exclusive_scan_index_sequence =
    typename exclusive_scan_index_sequence_impl<index_sequence<>,Init,IndexSequence>::type;

template<typename> void f();

int main()
{
  using ones = index_sequence<1,1,1,1,1>;

  using scanned = exclusive_scan_index_sequence<0,ones>;

  using expected = index_sequence<0,1,2,3,4>;

  assert((std::is_same<expected,scanned>::value));

  return 0;
}
