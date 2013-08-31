#include <functional>
#include <iostream>


struct SetId
{
    typedef int argument_type;
};


struct GetId
{
    typedef int result_type;
};


struct Increment
{
    typedef int argument_type;
    typedef int result_type;
};


struct Sum
{
    typedef std::tuple<int, int> argument_type;
    typedef int result_type;
};


struct Start
{
    // void(void)
};


template<typename C, typename Result = void> struct GetResultType { typedef void type; };
template<typename C> struct GetResultType<C, typename C::result_type> { typedef typename C::result_type type; };

template<typename C, typename Result = void> struct GetArgumentType { typedef void type; };
template<typename C> struct GetArgumentType<C, typename C::argument_type> { typedef typename C::argument_type type; };



    
template<typename C, typename R, typename A>
void do_check(R, A)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<typename> struct ResultTag {};
template<typename> struct ArgumentTag {};


template<typename C>
void check()
{
    do_check<C>(ResultTag<typename GetResultType<C>::type>{}, ArgumentTag<typename GetArgumentType<C>::type>{});
}


int main()
{
    check<SetId>();
    check<GetId>();
    check<Increment>();
    check<Sum>();
    check<Start>();
}