#include <boost/function.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <iostream>

int main()
{
    /*
     * suppose we have
     *     template<typename Thing> using pointer = Thing*;
     * then pointer<int()> is int (*)() and function<int()> is a more general version
     */
    
    int i = 2;
   
    /*
     * can't pass local type to function template
    struct local {
        int operator()() { return 3 * i; };
        // name's the same, as a pun
        int i;
    } local_object = { i };
     */
    
    namespace phx = boost::phoenix;
    using boost::proto::deep_copy;
    boost::function<int()> f = deep_copy(3 * phx::ref(i));
   
    std::cout << f() << '\n';
}