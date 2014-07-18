#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <string>
int fun(int a, std::string) {
    return 0;
}
int main()
{
    boost::function<int(std::string)> f = boost::bind(&fun, 0, _1);
    std::cout << f("aaa");
}
