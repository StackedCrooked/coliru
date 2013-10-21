#include <boost/variant.hpp>

#include <iostream>
#include <typeinfo>
#include <tuple>
#include <functional>

// Increment/Decrement operators
template<typename Tag>
struct inc_dec_op_generator
{
};
    
using inc_dec_op_preinc  = inc_dec_op_generator<struct tag_inc_dec_op_preinc>;
using inc_dec_op_predec  = inc_dec_op_generator<struct tag_inc_dec_op_predec>;
using inc_dec_op_postinc = inc_dec_op_generator<struct tag_inc_dec_op_postinc>;
using inc_dec_op_postdec = inc_dec_op_generator<struct tag_inc_dec_op_postdec>;
    
using inc_dec_op = boost::variant<
    inc_dec_op_preinc,
    inc_dec_op_predec,
    inc_dec_op_postinc,
    inc_dec_op_postdec>;

namespace visitor_galore // this is my make-shift replacement for typeswitch (I couldn't find it/make it work)
{
    template<typename T, class...Fs> struct visitor_t;

    template<typename T, class F1, class...Fs>
    struct visitor_t<T, F1, Fs...> : F1, visitor_t<T, Fs...>::type {
        typedef visitor_t type;
        visitor_t(F1 head, Fs...tail) : F1(head), visitor_t<T, Fs...>::type(tail...) {}
    
        using F1::operator();
        using visitor_t<T, Fs...>::type::operator();
    };

    template<typename T, class F> struct visitor_t<T, F> : F, boost::static_visitor<T> {
        typedef visitor_t type;
        visitor_t(F f) : F(f) {}
        using F::operator();
    };

    template<typename T=void, class...Fs>
    typename visitor_t<T, Fs...>::type make_visitor(Fs...x) { return {x...}; }
}

using visitor_galore::make_visitor;

#define Match(X) auto hidden_variable = X; run_invoker(X, make_visitor([](){}
#define EndMatch ));
#define Case(X) , [&](X)
#define Default() , [&](decltype(hidden_variable))

template<typename T, typename... Fs, typename... variant_types>
void run_invoker(boost::variant<variant_types...> variant, visitor_galore::visitor_t<T, Fs...> visitor)
{
    boost::apply_visitor(visitor, variant);
}

void pretty_print(inc_dec_op const& op)
{
    // The boost::variant library handles checking for exhausiveness,
    // which can be checked by outcommenting some of the lines below.
    // 
    // Do note, that no error is given, whenever a Default is around (obviously).
    //
    // There can be no braces after Match and before EndMatch (sadly), also no breaks are allowed.
    Match(op)
    //{
        Case(inc_dec_op_predec const&)
        {
            std::cout << "--var" << std::endl;
        }
        
        Case(inc_dec_op_preinc const&)
        {
            std::cout << "++var" << std::endl;
        }
        
        Case(inc_dec_op_postinc const&)
        {
            std::cout << "var++" << std::endl;
        }
        
        Case(inc_dec_op_postdec const&)
        {
            std::cout << "var--" << std::endl;
        }
        
        Default()
        {
            std::cout << "DEFAULT" << std::endl;
        }
    //}
    EndMatch;
}
    
int main()
{
    inc_dec_op var;
    
    var = inc_dec_op_preinc();
    pretty_print(var);
    var = inc_dec_op_postinc();
    pretty_print(var);
    var = inc_dec_op_postdec();
    pretty_print(var);
}