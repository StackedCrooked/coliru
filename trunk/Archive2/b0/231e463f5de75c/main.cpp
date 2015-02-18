#include <iostream>
#include <boost/parameter.hpp>
#include <boost/parameter/preprocessor.hpp>

BOOST_PARAMETER_NAME(x)
BOOST_PARAMETER_NAME(y)
BOOST_PARAMETER_NAME(z)

namespace tag { struct x; }

BOOST_PARAMETER_FUNCTION(
      (void),
      function,
      tag,
      (required (x, *))
      (optional
       (y, *, 2)
       (z, *, 3)
      )
)
{
   std::cout << "Called with x = " << x << " y = " << y << " z = " << z << std::endl;
}

int main()
{
   function(1, _z = 5);
   function(1, _y = 8);
}
