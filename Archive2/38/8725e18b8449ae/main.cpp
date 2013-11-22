#include <boost/units/dimension.hpp>
#include <boost/units/systems/si/pressure.hpp>
#include <boost/units/quantity.hpp>


using namespace boost::units;
using namespace boost::units::si;

struct MyClass
{
    quantity<pressure> press;  
};

int main() {
  
}