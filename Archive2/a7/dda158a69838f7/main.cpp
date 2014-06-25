#include <iostream>
#include <string>
#include <map>
//#include <boost/any.hpp>
#include <boost/variant.hpp>

using namespace boost;

typedef boost::variant< int, bool, std::string, std::map<std::string, std::string> > sstruct;

int    main(void)
{
	std::map<std::string, sstruct> sourceKeys;
	std::map<std::string, std::string> tmp;

	// int test
	sourceKeys["uk"] = "test";
	tmp["uk"] = "test";

	// depth test
	sourceKeys["usa"] = tmp["newyork"] = "jet";

//	std::cout << sourceKeys["usa"] << std::endl;
	std::cout << tmp["uk"] << std::endl;

	return 0;
}
