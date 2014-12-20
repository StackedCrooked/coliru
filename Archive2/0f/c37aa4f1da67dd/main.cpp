#include <boost/function_types/components.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/int.hpp>

template<typename F, int N>
class remove_first_N_param_types
{
    typedef typename boost::function_types::components<F>::type components;
    typedef typename boost::mpl::begin<components>::type beg;
    typedef typename boost::mpl::advance<beg, boost::mpl::int_<1  >>::type beg_param;
    typedef typename boost::mpl::advance<beg, boost::mpl::int_<1+N>>::type beg_param_plus_N;
    typedef typename boost::mpl::erase<components, beg_param, beg_param_plus_N>::type erased_first_N_params;
public:
    typedef typename boost::function_types::function_type<erased_first_N_params>::type type;
};

#include <iostream>

template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    typedef void ft(int, double, char, long);
    print_type<ft>();
    
    print_type< remove_first_N_param_types<ft, 2>::type >();
}