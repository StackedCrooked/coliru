#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

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
    virtual bool operator()(int i) const
    {
        std::cout << i << ' ';
        return false;
    }
};

void foo(std::vector<int> const& v, finder_base const& f)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    std::find_if(v.begin(), v.end(), f);
}

void bar(std::vector<int> const& v, finder const& f)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    std::find_if(v.begin(), v.end(), f);
}

void baz(std::vector<int> const& v, finder_base const& f)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    std::find_if(v.begin(), v.end(), std::ref(f));
}

int main()
{
    std::vector<int> v{1,2,3,4};
    finder f;
    
    foo(v, f);
    std::cout << "\n----\n";
    bar(v, f);
    std::cout << "\n----\n";
    baz(v, f);
    std::cout << "\n----\n";
}
