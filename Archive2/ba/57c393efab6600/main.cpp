#include<iostream>
#include<string>
#include<boost/tokenizer.hpp>

int main() {
   std::string s = "-0.003  79350   -0.267  147";
   boost::tokenizer<boost::char_separator<char> > tok(s, boost::char_separator<char>(" "));
   const auto n = std::distance( tok.begin(), tok.end() );
   std::cout << n << std::endl;
}