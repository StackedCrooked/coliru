#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

struct A
{
    std::string str() {return "asdf ";}
};

int main()
{
	std::vector<A*> vec(7);
	std::transform(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout), std::mem_fn(&A::str));
}