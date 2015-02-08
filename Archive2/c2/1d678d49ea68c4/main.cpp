#include <string>
#include <map>
#include <boost/regex.hpp>
#include <fstream>
#include <iterator>
#include <iostream>

// purpose: 
// takes the contents of a file in the form of a string 
// and searches for all the C++ class definitions, storing 
// their locations in a map of strings/int's 
typedef std::map<std::string, int, std::less<std::string> > map_type;

boost::regex expression(
   "^(template[[:space:]]*<[^;:{]+>[[:space:]]*)?"
   "(class|struct)[[:space:]]*"
   "(\\<\\w+\\>([[:blank:]]*\\([^)]*\\))?"
   "[[:space:]]*)*(\\<\\w*\\>)[[:space:]]*"
   "(<[^;:{]+>[[:space:]]*)?(\\{|:[^;\\{()]*\\{)");

void IndexClasses(map_type& m, const std::string& file)
{
   std::string::const_iterator start, end;
   start = file.begin();
   end = file.end();
      boost::match_results<std::string::const_iterator> what;
   boost::match_flag_type flags = boost::match_default;
   while(regex_search(start, end, what, expression, flags))
   {
      // what[0] contains the whole string 
      // what[5] contains the class name. 
      // what[6] contains the template specialisation if any. 
      // add class name and position to map: 
      m[std::string(what[5].first, what[5].second)
            + std::string(what[6].first, what[6].second)]
         = what[5].first - file.begin();
      // update search position: 
      start = what[0].second;
      // update flags: 
      flags |= boost::match_prev_avail;
      flags |= boost::match_not_bob;
   }
}

struct A 
{
    int i = 8 ;
};

class B 
{
    int j = 22 ;
};

template < typename T > class C {} ;

template<> class C<int> {} ;

int main()
{
    std::ifstream file( __FILE__ ) ;
    file >> std::noskipws ;
    
    map_type map ;
    
    std::istream_iterator<char> begin(file), end ;
    IndexClasses( map, std::string( begin, end ) ) ;
    
    for( const auto& pair : map ) 
        std::cout << "class '" << pair.first << "' at offset " << pair.second << '\n' ;
}
