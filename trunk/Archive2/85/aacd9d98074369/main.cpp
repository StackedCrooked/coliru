#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace boost::lambda;

struct X
{
    int x;
	std::string accessor() const { return "X[" + std::to_string(x) + "]"; } // I know, requires c++11
};

int main()
{
	std::vector<X> v;
	v.push_back({ 1 });
	v.push_back({2});
	v.push_back({3});
	v.push_back({4});
	v.push_back({5});

	std::for_each(v.begin(), v.end(), std::cout << boost::lambda::bind(&X::accessor, boost::lambda::_1) << "\n");
}
