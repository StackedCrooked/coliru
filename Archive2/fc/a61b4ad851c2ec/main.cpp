#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main(int, char**)
{
   string text = "( 123 , 356 )";

   char_separator<char> sep("(), ");
   tokenizer< char_separator<char> > tokens(text, sep);
   BOOST_FOREACH (const string& t, tokens) {
    cout << t << "." << endl;
  }
 }