#include <string>
#include <vector>

#include <boost/any.hpp>

int main()
{
    std::vector<boost::any> v;
    v.push_back(std::string { "Hi" });
    v.push_back(42);
}