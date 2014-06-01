#include <iostream>
#include <string>
#include <regex>

int main()
{
    const std::regex re( R"(\s*<([A-Z][A-Z0-9]*)\b[^>]*>(.*?)</\1>\s*)", std::regex::icase ) ;
    // std::regex::icase - ignore case
    // \s* - zero or more whitespace characters
    // /\1 - backreference to first sub-match (subexpression within parantheses)
    // .*? - non-greedy match of zero or more characters (the ? specifies non-greedy match)

    const std::string lines[] = { "<name>venros</name>", "<posts>47</posts>", "  <topic>C++ Regex -Reading HTML Tags</topic>  " } ;
    
    for( const std::string& str : lines )
    {
        std::smatch results ;
        if( std::regex_match( str, results, re ) )
        {
            std::cout << "tag: '" << results[1] // first sub-match - for ([A-Z][A-Z0-9]*)
                      << "'\tvalue: '" << results[2] // second sub-match - for (.*?)
                      << "'\n" ;
        }
    }
}
