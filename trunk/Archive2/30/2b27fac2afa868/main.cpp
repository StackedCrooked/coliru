#include <type_traits>
#include <vector>

static_assert(
  !std::is_same<
    std::random_access_iterator_tag,
    std::iterator_traits<std::vector<bool>::iterator>::iterator_category
  >::value,
  "libstdc++ std::vector::bool claims to be random access.");
static_assert(
  std::is_lvalue_reference<
    std::iterator_traits<std::vector<bool>::iterator>::reference
  >::value,
 "libstdc++ std::vector::bool SITS ON A THRONE OF LIES!");
