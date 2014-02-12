#include <string>
#include <iostream>

#define FUSION_MAX_VECTOR_SIZE  30
#define BOOST_PHOENIX_USE_V2_OVER_V3

#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>


namespace qi      = boost::spirit::qi;
namespace ascii   = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

using qi::double_;
using qi::char_;
using qi::lexeme;
using qi::int_;
using qi::lit;
using qi::_1;
using ascii::space;
using phoenix::ref;
using qi::parser;


class Test 
{
    // Class fields
    std::string test_str;
    public:

        Test(std::string& sample_str)
        {
            test_str = sample_str;
        }

        struct fruit
        {
            std::string name;
            std::string color;
        };
        struct person
        {
            std::string name;
            int age;
        };

        static void received_person(person& p)
        {
            std::cout << p.name << " with age"<< p.age<< " has been seen!"<<std::endl;
        }
        static void received_fruit(fruit& f)
        {
            std::cout << f.name << " is " << f.color << std::endl;
        }

        template <typename Iterator, typename Skipper = qi::space_type>
            struct MyGrammar : qi::grammar<Iterator, void(), Skipper>
        {
            MyGrammar() : MyGrammar::base_type(my_item)
            {
                my_item = 
                    *(
                          _fruit  [ boost::phoenix::bind(&received_fruit, qi::_1 )]
                        | _person [ boost::phoenix::bind(&received_person, qi::_1 )]
                     );

                _person = qi::lit('(') >> qi::lexeme [ *(qi::char_ - ',') ] >> ',' >> qi::int_ >> ')';
                _fruit  = qi::lit('[') >> qi::lexeme [ *(qi::char_ - ',') ] >> ',' >> qi::lexeme [ *(qi::char_ - ']') ] >> ']';
            }
            qi::rule<Iterator, void(), Skipper> my_item;
            qi::rule<Iterator, person(), Skipper> _person;
            qi::rule<Iterator, fruit()> _fruit;
        };

        void run()
        {
            typedef std::string::const_iterator iterator;
            MyGrammar <iterator, qi::space_type> my_grammar;

            iterator begin = test_str.begin();
            iterator end   = test_str.end();

            bool result_ = qi::phrase_parse(begin, end, my_grammar, qi::space) && begin == end;
            assert(result_);
        }
};

BOOST_FUSION_ADAPT_STRUCT
(
    Test::fruit,
    (std::string, name)
    (std::string, color))

BOOST_FUSION_ADAPT_STRUCT
(
    Test::person,
    (std::string, name)
    (int, age))

int main()
{
    std::string input("(jane, 23000)(david, 19)(mary, 30)[yello,100][green, 60.6][red, 30.5]");

    Test test(input);
    test.run();
}
