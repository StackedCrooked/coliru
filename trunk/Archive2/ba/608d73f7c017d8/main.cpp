#include <tuple>
#include <string>
#include <boost/fusion/functional/invocation/invoke.hpp>
 
void foo(int, std::string const&) {}
 
int main() {
    std::tuple<int, std::string> x = std::make_tuple(5, "Hello world!");
	boost::fusion::invoke(foo, x);
}