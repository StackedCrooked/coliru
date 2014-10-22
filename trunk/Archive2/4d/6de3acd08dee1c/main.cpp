
#include <iostream>
#include <string>
using namespace std;

#include <boost/uuid/sha1.hpp>
#include <boost/format.hpp>
 
 
string ToSHA1(const string s)
{
    boost::uuids::detail::sha1 sh;
	sh.process_bytes(s.c_str(), s.length());

	unsigned int digest[5];
	sh.get_digest(digest);

	string r;
	for(int i = 0; i < 5; ++i) {
		r += str(boost::format("%08x") % digest[i]);
	}

	return r;
}

int main()
{
	
	try {
		cout << ToSHA1("abcedfg") << endl;

	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cout << "unknown error" << endl;
	}

	return 0;
}