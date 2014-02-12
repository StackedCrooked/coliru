#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

#include <boost/ref.hpp>
#include <boost/bind.hpp>

struct finder_base
{
    virtual bool operator()(int i) const
    {
        std::cout << i << ' ';
        return true;
    }
};

struct finder : finder_base
{
    virtual bool operator()(int i) const override
    {
        std::cout << i << ' ';
        return false;
    }
};

void foo(std::vector<int> const& v, finder_base const& f)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    std::find_if(v.begin(), v.end(), std::ref(f));
}

void bar(std::vector<int> const& v, finder_base const& f)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    std::find_if(v.begin(), v.end(), boost::bind<bool>(boost::ref(f), _1));
}

int main()
{
    std::vector<int> v{1,2,3,4};
    finder f;
    
    foo(v, f);
    std::cout << "\n----\n";
    bar(v, f);
}
