#include <algorithm>
#include <iostream>
#include <iterator>
#include <boost/phoenix.hpp>

using namespace std;
using namespace boost::phoenix;
using namespace arg_names;

int main()
{
    signed char key[] = { 123, -41, -128, -6, -16, 56, 50, 3, -117, 25, -63, -92, -55, -79, 69, 69 };
	for (auto ch : key)
		cout << static_cast<int>(static_cast<uint8_t>(ch)) << ", ";
}