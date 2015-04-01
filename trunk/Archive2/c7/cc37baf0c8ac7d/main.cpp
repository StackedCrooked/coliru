#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   string s = "-0.003  79350   -0.267  147";
   boost::tokenizer<boost::char_separator<char> > tok(s, boost::char_separator<char>(" "));
   const auto n = std::distance( tok.begin(), tok.end() );
   std::cout << n << std::endl;
}