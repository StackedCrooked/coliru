#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    using namespace qi;

	using It     = std::string::const_iterator;
	using Token  = std::string;
	using Tokens = std::vector<Token>;

	rule<It, blank_type> label 
		= lexeme[+~char_(":")] >> ':'
		;

	rule<It, Token(), blank_type> token
		= lexeme[*~char_(",\n")];
		;

	rule<It, Tokens(), blank_type> line
		= label >> -(token % ',') >> eol
		;

	for (std::string const input : {
		"my first label: 123, 234, 345 with spaces\n",
		"1:\n",
		"2: \n",
		"3: ,,,\n",
		"4: ,  \t ,,\n",
		"5: ,  \t , something something,\n",
	})
	{
		std::cout << std::string(40, '=') << "\nparsing: '" << input << "'\n";

		Tokens parsed;
		auto f = input.begin(), l = input.end();
		bool ok = phrase_parse(f, l, line, blank, parsed);

		if (ok)
		{
			std::cout << "Tokens parsed successfully, number parsed: " << parsed.size() << "\n";
			for (auto token : parsed)
				std::cout << "token value '" << token << "'\n";
		}
		else
			std::cout << "Parse failed\n";

		if (f != l)
			std::cout << "Remaining input: '" << std::string(f, l) << "'\n";
	}
}