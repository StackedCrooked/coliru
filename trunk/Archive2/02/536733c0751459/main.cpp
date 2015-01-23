#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>

template <class Function>
void fill_vector(std::vector<int> &v, Function side)
{
    for(auto i=v.begin(); i!=v.end(); ++i)
    {
        *i = rand() % 100;
    }
    side(v);
}

class null_test
{
public:
    void operator() (std::vector<int> x) { }
};

class test
{
public:
    test() : max(0) { } 

    int max;
    void operator() (std::vector<int> x)
    { max = *std::max_element(x.begin(),x.end()); };
};

int main()
{
    std::vector<int> v(20);
    null_test n;
    fill_vector(v,n);

    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));

    std::cout << std::endl;

    std::vector<int> v2(20);
    test t;
    fill_vector(v2,std::ref(t));
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
    std::cout << t.max << std::endl;

    return 0;
}