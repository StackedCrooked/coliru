#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_rule.hpp>
#include <boost/spirit/include/classic_utility.hpp>

#include <string>

namespace spirit_classic = boost::spirit::classic;

template< typename Iterator >
static std::string getCodepage( Iterator first, Iterator last )
{
    std::string codepage;

    spirit_classic::parse(
        first,
        last,
        spirit_classic::as_lower_d[ "codepage" ]
            >> spirit_classic::ch_p( '=' )
            >> spirit_classic::lexeme_d[ spirit_classic::ch_p( '"' )
                >> ( +( spirit_classic::anychar_p - spirit_classic::ch_p( '"' ) ) )[spirit_classic::assign_a( codepage )]
                >> spirit_classic::ch_p( '"' ) ]
        >> spirit_classic::ch_p( ';' ),
         spirit_classic::comment_p( '#' ) | spirit_classic::space_p
        );

    if ( codepage.empty() )
    {
        codepage = "UTF-8";
    }

    return codepage;
}

int main()
{
    std::string input = "# Comment (optional)\n"
        "\n"
        "\n"
        "\n"
		"codepage = \"ISO-8859-2\"; \n";

	std::cout << getCodepage(input.begin(), input.end());
}
