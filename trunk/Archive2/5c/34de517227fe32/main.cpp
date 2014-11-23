#include <type_traits>

template <class T>
using is_scoped_enum = std::integral_constant<bool, !std::is_convertible<T, int>{}
                                                  && std::is_enum<T>{}>;

template <typename T>
struct myTemplate
{
   static_assert( is_scoped_enum<T>{}, "Invalid type argument!" );
};

enum  e1 {};
enum class e2 {};

// template struct myTemplate<int>;//fails
// template struct myTemplate<e1>; // fails
template struct myTemplate<e2>;

int main() {}
