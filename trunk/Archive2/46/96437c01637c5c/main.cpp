#include <iostream>
#include <boost/spirit/include/karma.hpp>

//START OF FULL.HPP
#include <boost/spirit/include/karma_generate.hpp>

///////////////////////////////////////////////////////////////////////////////
// definition the place holder 
namespace custom_generator 
{ 
    BOOST_SPIRIT_TERMINAL(full);
} 

///////////////////////////////////////////////////////////////////////////////
// implementation the enabler
namespace boost { namespace spirit 
{ 
    // We want custom_generator::full to be usable as a directive only, 
    // and only for generator expressions (karma::domain).
    template <>
    struct use_directive<karma::domain, custom_generator::tag::full> 
      : mpl::true_ {}; 
}}

///////////////////////////////////////////////////////////////////////////////
// implementation of the generator
namespace custom_generator
{ 
    template <typename T>
    struct adjust_size
    {
        static std::size_t call(std::size_t val)
        {
            return val; //with kleene and repeat just return the value
        }
    };

    template <typename Left, typename Right>
    struct adjust_size<boost::spirit::karma::list<Left,Right> >
    {
        static std::size_t call(std::size_t val)
        {
            return (val+1)/2; //with list you output n elements and n-1 semicolons
        }
    };
    // special delimiter wrapping the original one that counts the number of elements
    template <typename Delimiter>
    struct element_counter_delimiter 
    {
        element_counter_delimiter(Delimiter const& delim)
          : delimiter(delim), count(0) {}

        // This function is called during the actual delimiter output 
        template <typename OutputIterator, typename Context
          , typename Delimiter_, typename Attribute>
        bool generate(OutputIterator& sink, Context&, Delimiter_ const&
          , Attribute const&) const
        {
            // first invoke the wrapped delimiter
            if (!boost::spirit::karma::delimit_out(sink, delimiter))
                return false;

            // now we count the number of invocations 
            ++count;

            return true;
        }

        Delimiter const& delimiter;   // wrapped delimiter
        mutable unsigned int count;   // invocation counter
    };

    // That's the actual full generator
    template <typename Subject>
    struct full_container_generator
      : boost::spirit::karma::unary_generator<
            full_container_generator<Subject> >
    {
        // Define required output iterator properties
        typedef typename Subject::properties properties;

        // Define the attribute type exposed by this parser component
        template <typename Context, typename Iterator>
        struct attribute 
          : boost::spirit::traits::attribute_of<Subject, Context, Iterator> 
        {};

        full_container_generator(Subject const& s)
          : subject(s)
        {}

        // This function is called during the actual output generation process.
        // It dispatches to the embedded generator while supplying a new 
        // delimiter to use, wrapping the outer delimiter.
        template <typename OutputIterator, typename Context
          , typename Delimiter, typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx
          , Delimiter const& delimiter, Attribute const& attr) const
        {
            std::size_t elems_in_container = boost::spirit::traits::size(attr);
            element_counter_delimiter<Delimiter> d(delimiter);
            if (!subject.generate(sink, ctx, d, attr))
                return false;
            return elems_in_container == adjust_size<Subject>::call(d.count);
        }

        // This function is called during error handling to create
        // a human readable string for the error context.
        template <typename Context>
        boost::spirit::info what(Context& ctx) const
        {
            return boost::spirit::info("full", subject.what(ctx));
        }

        Subject subject;
    };
}

///////////////////////////////////////////////////////////////////////////////
// instantiation of the generator
namespace boost { namespace spirit { namespace karma
{
    // This is the factory function object invoked in order to create 
    // an instance of our full_container_generator.
    template <typename Subject, typename Modifiers>
    struct make_directive<custom_generator::tag::full, Subject, Modifiers>
    {
        typedef custom_generator::full_container_generator<Subject> result_type;

        result_type operator()(unused_type, Subject const& s, unused_type) const
        {
            return result_type(s);
        }
    };
}}}

//END OF FULL.HPP


int main()
{
    typedef std::ostream_iterator<char> iterator_t;
    namespace ka=boost::spirit::karma;

    std::string is1{"123"}, is2{"def"};
    std::vector<std::string> iv1{"123", "456"}, iv2{"123","def"}, iv3{"123", "456", "789"}, iv4{"123", "456", "def"};

    using custom_generator::full;

    ka::rule<iterator_t,std::string()> num = +ka::char_("0-9"); //this rule needs to have attribute std::string
                                                                //that wasn't the case with the original "auto num =..."
                                                                //and it caused that the delimiter count went way higher than it should
    ka::rule<iterator_t,std::vector<std::string>()> nums = full[num%ka::lit(";")];


    assert(ka::generate(iterator_t{std::cout}, num << ka::eol, is1) == true);
    assert(ka::generate(iterator_t{std::cout}, num << ka::eol, is2) == false);

    assert(ka::generate(iterator_t{std::cout}, nums << ka::eol, iv1) == true);
    assert(ka::generate(iterator_t{std::cout}, ka::buffer[nums << ka::eol], iv2) == false); //using buffer as mentioned by sehe
    assert(ka::generate(iterator_t{std::cout}, nums << ka::eol, iv3) == true);
    assert(ka::generate(iterator_t{std::cout}, ka::buffer[nums << ka::eol], iv4) == false);
}