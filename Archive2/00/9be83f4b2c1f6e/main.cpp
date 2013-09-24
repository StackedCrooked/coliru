#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

int main()
{
    std::map<std::string, unsigned> data;
    std::cin.unsetf(std::ios::skipws);

    {
        using namespace boost::spirit::qi;
        namespace phx = boost::phoenix;
        phrase_parse(
                boost::spirit::istream_iterator(std::cin), {},
                (as_string[+alpha] >> uint_) [ phx::ref(data)[_1] += _2 ] 
                % eol,
                blank);
    }

    std::cout << "Got #" << data.size() << " unique fruits\n";

    {
        using namespace boost::spirit::karma;
        std::cout << format(delimit(' ') [auto_] % eol, data);
    }
}
