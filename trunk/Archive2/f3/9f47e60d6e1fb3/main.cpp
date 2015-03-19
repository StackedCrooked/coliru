#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

typedef boost::shared_ptr<boost::unordered_map<int, std::string> > T;

int main() {
    boost::unordered_map<int, T> webData;
	webData[100] = T(new boost::unordered_map<int, std::string>());
	webData[100]->insert(std::make_pair(100, "json data returned"));
	return 0;
}
