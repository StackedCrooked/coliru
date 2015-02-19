#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>

int free_function() { return 0; }

int main()
{
    /*
     * suppose we have
     *     template<typename Thing> using pointer = Thing*;
     * then pointer<int()> is int (*)() and function<int()> is a more general version
     */
    
    struct local {
        static int static_member() { return 1; };
        int non_static_member() { return 2; };
    } local_object;
    struct functor {
        int operator()() { return 3; }
    } functor_object;
    boost::function<int()> fs[] = {
        &free_function,
        &local::static_member,
        boost::bind(&local::non_static_member, boost::ref(local_object)),
        functor_object,
        boost::ref(functor_object),
        // C++11
        [] { return 4; },
    };
    
    for(auto& f: fs) {
        std::cout << f() << '\n';
    }
}