#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

typedef boost::shared_ptr<boost::unordered_map<int, std::string> > T;

int main() {
    boost::unordered_map<int, T> webData;
    webData[100] = T(new T::element_type { { 100, "json data returned" } });
    webData[100]->emplace(200, "more json");
}