#include <tuple>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/include/vector_tie.hpp>

struct A { int first, second; };

BOOST_FUSION_ADAPT_STRUCT(A, (int, first)(int, second))

int main() {
  int a; int b;
  boost::fusion::vector_tie(a, b) = A { 1, 42 };
  return b;
}