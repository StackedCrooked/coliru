#include <iterator>
#include <boost/regex.hpp>
#include <regex>
#include <string>
 
int main()
{
          string str = "hey guys";
	      string repl = "girls";
	      regex rx("guys");
	      str = std::regex_replace(str, rx ,repl);
	      cout <<"str: " << str << endl;
}