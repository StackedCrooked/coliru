
#include <iostream>
#include <algorithm>
#include <limits>
#include <random>
#include <sstream>
using namespace std;

#include <boost/format.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
namespace bmp = boost::multiprecision;
typedef bmp::cpp_int INT;


INT RND_INT(int bytes)
{
    random_device rd;	
	std::mt19937 rnd(rd());
	INT r;

	if (bytes < 8) {
		std::uniform_int_distribution<uint32_t> dist(1, numeric_limits<uint32_t>().max());
		r = dist(rnd);
	}
	else {
		std::uniform_int_distribution<uint64_t> dist(1, numeric_limits<uint64_t>().max());
		int loop = bytes / 8;

		for (int i = 0; i < loop; ++i) {
			r |= (INT(dist(rnd)) << (64 * i));
		}
	}

	return r;
}

INT RND_Prime(int bytes)
{
	INT r(0);

	for (int i = 0; i < 1024; ++i) {
		INT n = RND_INT(bytes);

		bool b = bmp::miller_rabin_test(n, 25);
		if (b) {
			r = n;
			cout << "find : " << i << ", prime nmber is " <<  endl;
			cout << str(boost::format("%X") % n) << endl << endl;
			break;
		}	
	}

	return r;
}



void DHC_TEST()
{
	INT P = RND_Prime(16);
	if (P == 0) {
		throw logic_error("DHC_TEST : prime number failed ");
	}
	const INT G = RND_INT(8);

	const INT privateA = RND_INT(8);
	const INT privateB = RND_INT(8);

	cout << "ali private : " << endl <<  str(boost::format("%X") % privateA) << endl;
	cout << "bob private : " << endl <<  str(boost::format("%X") % privateB) << endl;
	cout << endl;

	auto publicA = bmp::powm(G, privateA, P);		
	auto publicB = bmp::powm(G, privateB, P);

	cout << "ali public : " << endl <<  str(boost::format("%X") % publicA) << endl;
	cout << "bob public : " << endl <<  str(boost::format("%X") % publicB) << endl;
	cout << endl;

	cout << "ali block key : " << endl <<  str(boost::format("%032X") % bmp::powm(publicB, privateA, P)) << endl;
	cout << "bob block key : " << endl <<  str(boost::format("%032X") % bmp::powm(publicA, privateB, P)) << endl;

}


int main()
{
	
	try {
		DHC_TEST();	
	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cout << "unknown error" << endl;
	}

	return 0;
}


