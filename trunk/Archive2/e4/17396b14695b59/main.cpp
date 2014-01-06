#include <iostream>
#include <boost/regex.hpp>
#include <string>

//bool MatchWithGrep(string& pattern, string& data)
bool MatchWithGrep( const std::string& pattern, const std::string& data )
{
    // const boost::regex e(pattern.c_str(), boost::regex::grep);
	const boost::regex e( pattern, boost::regex::grep ) ;
	// return regex_match(data.c_str(), e);
	return boost::regex_match( data, e ) ;

}

int main()
{
    const std::string& pattern = "a*\n123" ;
    const char* const test_data[] = { "aaa", "123", "aaa123", "aaa\\n123", "aaaba" } ;
    
    for( auto cstr : test_data )
        std::cout << cstr << ": " << ( MatchWithGrep( pattern, cstr ) ? "match" : "no match" ) << '\n' ;
}
