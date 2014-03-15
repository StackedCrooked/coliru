//http://coliru.stacked-crooked.com/
#include <iostream>
#include <boost/tokenizer.hpp>
using namespace std;
using namespace boost;

int main() {
    string s = "1 -3.456 ";
    typedef char_separator<char> sep;
	typedef tokenizer<sep> tok;
    tok ko(s,sep(" "));
    for(const auto& t:ko)
        cout<<"("<<t<<")";
	return 0;
}