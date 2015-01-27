#include <string>
#include <regex>
#include <iostream>

    std::string get_name( std::string const& src ) {
      static std::regex re( R"-(Hello my name is: (\w+) have a good day!)-" ); 
      std::smatch results;
      bool bworked = std::regex_match( src, results, re );
      if (!bworked) return {};
      // Assert(results.size() >= 2);
      if (results.size() < 2) return {};
      return results.str(1);
    }
int main() {
    auto s = get_name( "Hello my name is: abc have a good day!" );
    std::cout << "name is: \"" << s.c_str() << "\"\n";
}