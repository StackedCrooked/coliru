#include <boost/variant.hpp>

using V = boost::variant<int64_t, long double>;

int main()
{
    V a = 42l,
      b = 3.14l,
      c = 42ll
      ;

}
