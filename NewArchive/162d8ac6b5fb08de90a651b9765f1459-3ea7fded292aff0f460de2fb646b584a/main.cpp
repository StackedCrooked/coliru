#include <iostream>
#include <string>
#include <vector>

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

//START OF CURRENT_POS.HPP
#include <boost/spirit/include/karma_generate.hpp>

///////////////////////////////////////////////////////////////////////////////
// definition the place holder
namespace custom_generator {
  BOOST_SPIRIT_TERMINAL_EX(current_pos);

  struct position_getter: boost::spirit::terminal<
      boost::spirit::tag::stateful_tag<std::size_t&, tag::current_pos> > {
    typedef boost::spirit::tag::stateful_tag<std::size_t&, tag::current_pos> tag_type;

    position_getter(std::size_t& p)
        : boost::spirit::terminal<tag_type>(p) {
    }
  };
}

///////////////////////////////////////////////////////////////////////////////
// implementation the enabler
namespace boost {
  namespace spirit {

    // enables current_pos(reference)
    template<>
    struct use_terminal<karma::domain,
        tag::stateful_tag<std::size_t&, custom_generator::tag::current_pos> > : mpl::true_ {
    };
  }
}

///////////////////////////////////////////////////////////////////////////////
// implementation of the generator
namespace custom_generator {
  struct current_pos_generator: boost::spirit::karma::primitive_generator<
      current_pos_generator> {
    current_pos_generator(std::size_t& pos_)
        : pos(pos_) {
    }

    // Define required output iterator properties
    typedef typename boost::mpl::int_<
        boost::spirit::karma::generator_properties::tracking> properties;

    // Define the attribute type exposed by this parser component
    template<typename Context, typename Unused>
    struct attribute {
      typedef boost::spirit::unused_type type;
    };

    // This function is called during the actual output generation process.
    // It dispatches to the embedded generator while supplying a new
    // delimiter to use
    template<typename OutputIterator, typename Context, typename Delimiter,
        typename Attribute>
    bool generate(OutputIterator& sink, Context& ctx,
                  Delimiter const& delimiter, Attribute const& attr) const {

      std::size_t column = sink.get_out_count();

      // This would only work if you comment "private:" in line 82 of
      // boost/spirit/home/karma/detail/output_iterator.hpp
      // std::size_t column = sink.track_position_data.get_column()-1;

      pos = column;

      return true;
    }

    // This function is called during error handling to create
    // a human readable string for the error context.
    template<typename Context>
    boost::spirit::info what(Context& ctx) const {
      return boost::spirit::info("current_pos");
    }

    std::size_t& pos;
  };
}

///////////////////////////////////////////////////////////////////////////////
// instantiation of the generator
namespace boost {
  namespace spirit {
    namespace karma {
      template<typename Modifiers>
      struct make_primitive<
          tag::stateful_tag<std::size_t&, custom_generator::tag::current_pos>,
          Modifiers> {
        typedef custom_generator::current_pos_generator result_type;

        template<typename Terminal>
        result_type operator()(Terminal& term, unused_type) const {
          typedef tag::stateful_tag<std::size_t&,
              custom_generator::tag::current_pos> tag_type;
          using spirit::detail::get_stateful_data;
          return result_type(get_stateful_data<tag_type>::call(term));
        }
      };
    }
  }
}
//END OF CURRENT_POS.HPP

int main() {
  std::vector<int> v { 0, 1, 2, 3 };
  {
    namespace karma = boost::spirit::karma;
    namespace phx = boost::phoenix;
    using custom_generator::position_getter;

    std::size_t start = 0, end = 0;
    position_getter start_(start), end_(end);

    karma::rule<std::ostream_iterator<char>, std::vector<int>()> myRule =
        start_
            << karma::lit("Some text: ")
            << end_
            << karma::int_ % (karma::eol
                << karma::repeat(phx::ref(end) - phx::ref(start))[karma::char_(
                    " ")]);
    karma::generate(std::ostream_iterator<char>(std::cout), myRule, v);

    std::cout << std::endl;

    karma::rule<std::ostream_iterator<char>, std::vector<int>()> myRuleThatAlsoWorks =
        karma::lit(":)")
            << karma::eol
            << start_
            << karma::lit("Some text: ")
            << end_
            << karma::int_ % (karma::eol
                << karma::repeat(phx::ref(end) - phx::ref(start))[karma::char_(
                    " ")]);
    karma::generate(std::ostream_iterator<char>(std::cout), myRuleThatAlsoWorks,
                    v);

  }

  return 0;
}
