// STD HEADER
#include <iostream>
#include <string>
#include <complex>

// BOOST HEADER
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    class employee
    {
    public:
        // must be default constructible
        employee (
            int _age = 0
          , std::string _surname = ""
          , std::string _forename = ""
          , double _salary = 0
        );

        friend std::ostream& operator<<(std::ostream& os, employee const& e) {
            return os << "employee[" << e.age_ << ", " << e.forename_ << ", " << e.surname_ << ", " << e.salary_ << "]";
        }
    private:
        int age_;
        std::string surname_;
        std::string forename_;
        double salary_;
    };

    employee::employee (
        int _age
      , std::string _surname
      , std::string _forename
      , double _salary
    ) : age_(_age)
      , surname_(_surname)
      , forename_(_forename)
      , salary_(_salary)
    {
    }

}

namespace client
{
    template <typename Iterator>
    struct employee_parser
      : qi::grammar<Iterator, employee(), ascii::space_type>
    {
        employee_parser() : employee_parser::base_type(start)
        {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using ascii::char_;

            quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];

            start =
                lit("employee")
                >> ('{'
                >>  int_ >> ','
                >>  quoted_string >> ','
                >>  quoted_string >> ','
                >>  double_
                >>  '}'
                ) [ qi::_val = boost::phoenix::construct<employee>(qi::_1, qi::_2, qi::_3, qi::_4) ]
                ;
        }

        qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
        qi::rule<Iterator, employee(), ascii::space_type> start;
    };
}

int main()
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tAn employee parser for Spirit...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Give me an employee of the form :"
        << "employee{age, \"surname\", \"forename\", salary } \n";
    std::cout << "Type [q or Q] to quit\n\n";

    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef client::employee_parser<iterator_type> employee_parser;

    employee_parser g;
    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        client::employee emp;
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, g, space, emp);

        if (r && iter == end)
        {
            std::cout << boost::fusion::tuple_open('[');
            std::cout << boost::fusion::tuple_close(']');
            std::cout << boost::fusion::tuple_delimiter(", ");

            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "Parsed: " << emp << "\n"
            std::cout << "\n-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}
