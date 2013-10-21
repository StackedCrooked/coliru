template<int...>
struct Sequence
{
};

template<int N, int... S>
struct GenerateSequence : GenerateSequence<N-1, N-1, S...>
{
};

template<int... S>
struct GenerateSequence<0, S...> 
{
  typedef Sequence<S...> type;
};

template<int N, int... S>
struct GenerateSequenceBreak1 : GenerateSequenceBreak1<N-1, N, S...>
{
};

template<int... S>
struct GenerateSequenceBreak1<0, S...> 
{
  typedef Sequence<S...> type;
};

#include <boost/variant.hpp>

#include <iostream>
#include <typeinfo>
#include <tuple>
#include <functional>

template<typename CAR, typename... CDR>
CAR getCar(std::tuple<CAR, CDR...> tup)
{
    return std::get<0>(tup);
}

template<typename CAR, typename... CDR, int... S>
std::tuple<CDR...> getCdrHelper(std::tuple<CAR, CDR...> tup, Sequence<S...>)
{
    return std::make_tuple(std::get<S>(tup)...);
}

template<typename CAR, typename... CDR>
std::tuple<CDR...> getCdr(std::tuple<CAR, CDR...> tup)
{
    return getCdrHelper(tup, typename GenerateSequenceBreak1<sizeof...(CDR)>::type());
}

template<typename... REST>
struct visitor
{
};

template<>
struct visitor<>
{
    visitor(std::tuple<>)
    {
    }
};

template<typename T, typename... REST>
struct visitor<T, REST...> : public boost::static_visitor<>, public visitor<REST...>
{
    using super = visitor<REST...>;
    visitor(std::tuple<T, REST...> std_functions)
    : function(getCar(std_functions)), super(getCdr(std_functions))
    {
    }
    
    void operator()(typename T::argument_type arg) const
    {
        //std::cout << typeid(typename T::argument_type).name() << "called" << std::endl;
        function(arg);
    }
    
    T function;
};

template<typename... T>
struct Matcher
{
    Matcher(std::tuple<T...> std_functions)
    : std_functions(std_functions)
    {
    }
    
    void invoke(boost::variant<typename T::argument_type...> variant)
    {
        std::cout << "INVOKE" << std::endl;
        visitor<T...> visitor{std_functions};
        std::cout << "INVOKE" << std::endl;
        boost::apply_visitor(visitor, variant);
        std::cout << "INVOKE" << std::endl;
    }
    
    std::tuple<T...> std_functions;
};

template<typename... T>
Matcher<T...> make_matcher(T... args)
{
    std::tuple<T...> std_functions = std::make_tuple(args...);
    return Matcher<T...>(std_functions);
}

    // Increment/Decrement operators
    template<typename Tag>
    struct inc_dec_op_generator
    {
    };
    
    struct tag_inc_dec_op_preinc {};
    struct tag_inc_dec_op_predec {};
    struct tag_inc_dec_op_postinc {};
    struct tag_inc_dec_op_postdec {};
    
    using inc_dec_op_preinc  = inc_dec_op_generator<struct tag_inc_dec_op_preinc>;
    using inc_dec_op_predec  = inc_dec_op_generator<struct tag_inc_dec_op_predec>;
    using inc_dec_op_postinc = inc_dec_op_generator<struct tag_inc_dec_op_postinc>;
    using inc_dec_op_postdec = inc_dec_op_generator<struct tag_inc_dec_op_postdec>;
    
    using inc_dec_op = boost::variant<
        inc_dec_op_preinc,
        inc_dec_op_predec,
        inc_dec_op_postinc,
        inc_dec_op_postdec>;

/*
    void pretty_print(inc_dec_op const& op)
    {
    boost::apply_visitor(
                make_visitor(
                    [](inc_dec_op_predec const&)  { std::cout << "--var"; }, 
                    [](inc_dec_op_preinc const&)  { std::cout << "++var"; }, 
                    [](inc_dec_op_postinc const&) { std::cout << "var++"; }, 
                    [](inc_dec_op_postdec const&) { std::cout << "var--"; }
                    )
                , op);
    }
*/    
int main()
{
    inc_dec_op var;
    
    var = inc_dec_op_preinc();
    //var = inc_dec_op_postdec();
    auto matcher = 
    make_matcher( 
        std::function<void(inc_dec_op_preinc const&)>([](inc_dec_op_preinc const&)  { std::cout << "++var"; })//, 
        //std::function<void(inc_dec_op_predec const&)>([](inc_dec_op_predec const&)  { std::cout << "--var"; }), 
        //std::function<void(inc_dec_op_postinc const&)>([](inc_dec_op_postinc const&) { std::cout << "var++"; }), 
        //std::function<void(inc_dec_op_postdec const&)>([](inc_dec_op_postdec const&) { std::cout << "var--"; })
        );
    matcher.invoke(var);
}