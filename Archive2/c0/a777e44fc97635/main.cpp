#include <boost/function.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <iostream>

int main()
{
    /*
     * suppose we have
     *     template<typename Thing> using pointer = Thing*;
     * then pointer<int(int)> is int (*)(int) and function<int(int)> is a more general version
     */
    
    int i = 2;
   
    /*
     * can't pass local type to function template
    struct local {
        int operator()(int arg) { return 3 * i + 4 * arg; };
        // name's the same, as a pun
        int i;
    } local_object = { i };
     */
    
    namespace phx = boost::phoenix;
    using namespace phx::placeholders;
    using boost::proto::deep_copy;
    boost::function<int(int)> f = deep_copy(3 * phx::ref(i) + 4 * arg1);
   
    std::cout << f(1) << '\n';
}