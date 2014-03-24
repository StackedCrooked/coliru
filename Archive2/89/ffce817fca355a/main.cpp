#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>
 
int main()
{
   std::string text = "Quick brown fox.";
   // tokenization (non-matched fragments)
   // Note that regex is matched only two times: when the third value is obtained
   // the iterator is a suffix iterator.
   std::regex ws_re("\\s+"); // whitespace
   std::copy( std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1),
              std::sregex_token_iterator(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
 
   // iterating the first submatches
   std::string html = "<p><a href=\"http://google.com\">google</a> "
                      "< a HREF =\"http://cppreference.com\">cppreference</a>\n</p>";
   std::regex url_re("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"", std::regex::icase);
   std::copy( std::sregex_token_iterator(html.begin(), html.end(), url_re, 1),
              std::sregex_token_iterator(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
}