#include <iostream>
#include <string>
#include <vector>

#include <boost/spirit/include/karma.hpp>

//START OF GENERATE_IF_TRUE.HPP
#include <boost/spirit/include/karma_generate.hpp>

///////////////////////////////////////////////////////////////////////////////
// definition the place holder 
namespace custom_generator 
{ 
    BOOST_SPIRIT_TERMINAL(generate_if_true);
} 

///////////////////////////////////////////////////////////////////////////////
// implementation the enabler
namespace boost { namespace spirit 
{ 
    // We want custom_generator::generate_if_true to be usable as a directive only, 
    // and only for generator expressions (karma::domain).
    template <>
    struct use_directive<karma::domain, custom_generator::tag::generate_if_true> 
      : mpl::true_ {}; 
}}

///////////////////////////////////////////////////////////////////////////////
// implementation of the generator
namespace custom_generator
{ 


    // That's the actual generate_if_true generator
    template <typename Subject>
    struct generate_if_true_generator
      : boost::spirit::karma::unary_generator<
            generate_if_true_generator<Subject> >
    {
        // Define required output iterator properties: take the properties needed by the subject
        typedef typename Subject::properties properties;

        // Define the attribute type exposed by this generator component
        template <typename Context, typename Iterator>
        struct attribute 
        {
            typedef bool type;
        };

        generate_if_true_generator(Subject const& s)
          : subject(s)
        {}

        // This function is called during the actual output generation process.
        // It dispatches to the embedded generator while supplying a new 
        // delimiter to use
        template <typename OutputIterator, typename Context
          , typename Delimiter, typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx
          , Delimiter const& delimiter, Attribute const& attr) const
        {
            using boost::spirit::unused;

            if(attr)
                subject.generate(sink,ctx,delimiter,unused); //the subject generator must have an unused attribute
                                                             //if it has an attribute I think an optional would work fine
            return true;
        }

        // This function is called during error handling to create
        // a human readable string for the error context.
        template <typename Context>
        boost::spirit::info what(Context& ctx) const
        {
            return boost::spirit::info("generate_if_true", subject.what(ctx));
        }

        Subject subject;
    };
}

///////////////////////////////////////////////////////////////////////////////
// instantiation of the generator
namespace boost { namespace spirit { namespace karma
{
    // This is the factory function object invoked in order to create 
    // an instance of our generate_if_true_generator.
    template <typename Subject, typename Modifiers>
    struct make_directive<custom_generator::tag::generate_if_true, Subject, Modifiers>
    {
        typedef custom_generator::generate_if_true_generator<Subject> result_type;

        result_type operator()(unused_type, Subject const& s, unused_type) const
        {
            return result_type(s);
        }
    };
}}}
//END OF GENERATE_IF_TRUE.HPP

namespace karma = boost::spirit::karma;

int main()
{
    using custom_generator::generate_if_true;

    for (bool const_qualifier : { true, false })
    {   
        std::cout << karma::format_delimited("void foo()" << generate_if_true["const"], ' ', const_qualifier) << "\n";
    }   
}