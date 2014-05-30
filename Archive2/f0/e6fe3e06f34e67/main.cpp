#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
      std::string text = "move \t  the first word in a line of text to  \t  the end" ;
      std::cout << text << '\n' ;

      // locate the first white space
      const auto first_ws = std::find_if( text.begin(), text.end(), []( char c ) { return std::isspace(c) ; } ) ;
      const auto next_non_ws = std::find_if( first_ws, text.end(), []( char c ) { return !std::isspace(c) ; } ) ;

      if( next_non_ws != text.end() ) // if text contains more than one word
      {
          // rotate to get the trailing white spaces before the first word
          std::rotate( text.begin(), first_ws, next_non_ws ) ;

          // rotate to get the leading whitespaces and first word at the end
          std::rotate( text.begin(), next_non_ws, text.end() ) ;

      }

      std::cout << text << '\n' ;
}
