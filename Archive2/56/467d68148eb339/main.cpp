
//START OF PHOENIX_MAKE_SHARED.HPP

#ifndef BOOST_PHOENIX_MAKE_SHARED_HPP
#define BOOST_PHOENIX_MAKE_SHARED_HPP

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(make_shared)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , BOOST_PHOENIX_COMPOSITE_LIMIT
)

namespace boost { namespace phoenix
{
    struct make_shared_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename A0,typename Context>
        struct result<This(A0, Context)>
        {
            typedef boost::shared_ptr<typename detail::result_of::target<A0>::type > type;
        };

        template <typename Target, typename Context>
        typename boost::shared_ptr<typename detail::result_of::target<Target>::type>
        operator()(Target, Context const &) const
        {
            return boost::make_shared<typename detail::result_of::target<Target>::type>();
        }
        
        #define EVAL_a(_,N,__)                                                                \
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(N)) boost::phoenix::eval(a ## N, ctx)
        
        #define GENERATE_MAKE_SHARED_EVAL(_,N,__)                                             \
        template <typename This, BOOST_PHOENIX_typename_A(N), typename Context>               \
        struct result<This(BOOST_PHOENIX_A(N), Context)>                                      \
        {                                                                                     \
            typedef boost::shared_ptr<typename detail::result_of::target<A0>::type > type;    \
        };                                                                                    \
    	template <BOOST_PHOENIX_typename_A(N), typename Context>                              \
        typename boost::shared_ptr<typename detail::result_of::target<A0>::type >             \
        operator()(                                                                           \
            A0 const&                                                                         \
          , BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(                                              \
                N                                                                             \
              , A                                                                             \
              , const& a                                                                      \
            )                                                                                 \
          , Context const & ctx                                                               \
        ) const                                                                               \
        {                                                                                     \
            return                                                                            \
                boost::make_shared<typename detail::result_of::target<A0>::type>(             \
                    BOOST_PP_REPEAT_FROM_TO(                                                  \
                        1                                                                     \
                      , N                                                                     \
                      , EVAL_a, _                                                             \
                    )                                                                         \
                );                                                                            \
        }
        
        
        BOOST_PP_REPEAT_FROM_TO(2,BOOST_PHOENIX_COMPOSITE_LIMIT,GENERATE_MAKE_SHARED_EVAL,_)
        
        #undef EVAL_a
        
        #undef GENERATE_MAKE_SHARED_EVAL
        

    };

    template <typename Dummy>
    struct default_actions::when<rule::make_shared, Dummy>
        : call<make_shared_eval, Dummy>
    {};

    template <typename T>
    inline
    typename expression::make_shared<detail::target<T> >::type const
    make_shared()
    {
        return
            expression::
                make_shared<detail::target<T> >::
                    make(detail::target<T>());
    }
    
    #define GENERATE_MAKE_SHARED(_,N,__)                                                        \
        template <typename T, BOOST_PHOENIX_typename_A(N)>                                      \
        inline                                                                                  \
        typename expression::make_shared<detail::target<T>, BOOST_PHOENIX_A(N)>::type const     \
        make_shared(BOOST_PHOENIX_A_const_ref_a(N))                                             \
        {                                                                                       \
            return                                                                              \
                expression::                                                                    \
                    make_shared<detail::target<T>, BOOST_PHOENIX_A(N)>::                        \
                        make(detail::target<T>(), BOOST_PHOENIX_a(N));                          \
        }
        
    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PHOENIX_COMPOSITE_LIMIT,GENERATE_MAKE_SHARED,_)
    
    #undef GENERATE_MAKE_SHARED


}}

#endif

//END OF PHOENIX_MAKE_SHARED.HPP

#include <iostream>
#include <string>
#include <vector>

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace phx=boost::phoenix;
namespace qi=boost::spirit::qi;

struct foo
{
    foo():foo1(1),foo2(1.1){}
    foo(int foo1_):foo1(foo1_),foo2(2.2){}
    foo(int foo1_, double foo2_):foo1(foo1_),foo2(foo2_){}
    int foo1;
    double foo2;
};


int main()
{
    //using phx::arg_names::arg1;
    //using phx::arg_names::arg2;
    //boost::shared_ptr<foo> var1 = phx::make_shared<foo>()();
    //boost::shared_ptr<foo> var2 = phx::make_shared<foo>(arg1)(2);
    //boost::shared_ptr<foo> var3 = phx::make_shared<foo>(arg1,arg2)(3,3.3);
    
    //std::cout << "var1: " << var1->foo1 << ", " << var1->foo2 << std::endl;
    //std::cout << "var2: " << var2->foo1 << ", " << var2->foo2 << std::endl;
    //std::cout << "var3: " << var3->foo1 << ", " << var3->foo2 << std::endl;
    
    std::string test = "default,2,3-3.3";
    
    qi::rule<std::string::const_iterator,boost::shared_ptr<foo>()> awful_rule =
              qi::lit("default")[qi::_val=phx::make_shared<foo>()]
            | (qi::int_ >> !qi::lit('-'))[qi::_val=phx::make_shared<foo>(qi::_1)]
            | (qi::int_ >> qi::lit('-') >> qi::double_)[qi::_val=phx::make_shared<foo>(qi::_1,qi::_2)]
            ;
    qi::rule<std::string::const_iterator,std::vector<boost::shared_ptr<foo> >()> parser = awful_rule%qi::lit(',');
    
    std::string::const_iterator iter=test.begin(), end=test.end();
    
    std::vector<boost::shared_ptr<foo> > foo_vector;
    bool result = qi::parse(iter, end, parser, foo_vector);
    
    if(result && (iter==end) )
    {
        std::cout << "Success:" << std::endl;
        
        for(std::size_t cont=0; cont < foo_vector.size(); ++cont)
            std::cout << foo_vector[cont]->foo1 << ", " << foo_vector[cont]->foo2 << std::endl;
    }
    else
    {
        std::cout << "Failure. Unparsed: " << std::string(iter,end) << std::endl;
    }
}
