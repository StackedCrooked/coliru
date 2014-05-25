#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/callable.hpp>

using namespace boost::type_erasure;
namespace mpl = boost::mpl;

struct A { void operator()(int){ std::cout << "A" << std::endl;} void operator()(double){ std::cout << "A" << std::endl;} };
struct B { void operator()(int){ std::cout << "B" << std::endl;} void operator()(double){ std::cout << "B" << std::endl;} };

int main(int argc, const char * argv[])
{
   A a; B b;

   any < mpl::vector <
      callable<void(int)>,
      callable<void(double)>,
      copy_constructible<>,
      relaxed //ADDED
   >> x = a, y = b;
   
   x(1);
   y(1);

   x = y; // rebind x to b, doesn't compile

   x(1);
   return 0;
}