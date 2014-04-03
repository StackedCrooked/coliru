#include <iostream>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>

int main()
{
     bool boo = true;

     // with boost.lambda
     using boost::lambda::_1;
     boost::function<void(bool&)> lam = _1 = !_1;

     std::cout << "before lambda call, boo = " << std::boolalpha << boo << '\n';
     lam(boo);
     std::cout << "after lambda call, boo = " << boo << "\n\n";

     // wrapping in boost.bind
     boost::function<void()> blam = boost::bind<void>(_1 = !_1, boost::ref(boo));

     std::cout << "before bound lambda call, boo = " << boo << '\n';
     blam();
     std::cout << "after bound lambda call, boo = " << boo << "\n\n";

     // with boost.phoenix
     using boost::phoenix::arg_names::arg1;
     boost::function<void(bool&)> pho = arg1 = !arg1;

     std::cout << "before phoenix call, boo = " << boo << '\n';
     pho(boo);
     std::cout << "after phoenix call, boo = " << boo << "\n\n";

     // wrapping in boost.bind
     boost::function<void()> phlam = boost::bind<void>(arg1 = !arg1, boost::ref(boo));

     std::cout << "before bound lambda call, boo = " << boo << '\n';
     phlam();
     std::cout << "after bound lambda call, boo = " << boo << "\n\n";
}
