#include <cstdlib>
#include <iostream>
#include <boost/coroutine/all.hpp>


using Pull = boost::coroutines::asymmetric_coroutine<std::string>::pull_type;
using Push   = boost::coroutines::asymmetric_coroutine<std::string>::push_type;


Push push([&](Pull& pull)
{
    while (true)
    {
        std::cout << pull.get() << ' ';
        pull();
    }
});


int main()
{
    push("1");
    push("2");
    push("3");
    push("a");
    push("b");
    push("c");
    std::cout << "\nEnd of program.\n";
}
