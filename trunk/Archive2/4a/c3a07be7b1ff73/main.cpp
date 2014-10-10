#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/version.hpp>

int main(int argc, char* argv[])
{
    using namespace std;
	
	vector<string> args { argv, argv + argc };
	boost::sort(args, [] (const string& a, const string& b) {
			try
			{
				throw runtime_error("test");
			} catch(exception& ex)
			{
			}
			return a < b;
		});
	boost::copy(args, ostream_iterator<string>(cout, " "));

    return 0;
}
