#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <vector>
#include <iostream>

struct foo
{
    int getRandomNumber() { return 42; }
};

void bar(boost::shared_ptr<foo> f)
{
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), boost::bind(&foo::getRandomNumber, f));
    
    for(auto const& i : v) {
        std::cout << i << ' ';
    }
}

int main()
{
    auto f = boost::make_shared<foo>();
    bar(f);
}
