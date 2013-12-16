#include <boost/tuple/tuple.hpp>

int main()
{
typedef boost::tuple<std::string, std::string> My_tuple;
My_tuple tup = boost::make_tuple("", "");

boost::get<0>(tup) = "StringA";
boost::get<1>(tup) = "StringB";

tup = boost::tie("first", "second");
}
