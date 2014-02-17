#include <type_traits>

using namespace std;

using int_ref = int&;

static_assert(is_same<int const&,int_ref const&&>(), "Jabberwocky is killing user.");