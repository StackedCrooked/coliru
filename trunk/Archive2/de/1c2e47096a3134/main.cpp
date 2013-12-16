#include <cmath>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <map>
#include <boost/iterator/transform_iterator.hpp>

using namespace std;

int square(int n)
{
    return n*n;
}

int add(int n, int m)
{
    return n+m;
}

// iterator_adaptor helps readability when creating transform_iterators
template <class F>
class iterator_adaptor {
    
    F func;

public:
    iterator_adaptor( F f ) : func(f) {   }
    
    template<typename Iter>
    boost::transform_iterator<F, Iter> operator() (Iter it) {
        return boost::make_transform_iterator(it, func);  
    }

};

template <typename F>
iterator_adaptor<F> make_adaptor( F fun ) {
    return iterator_adaptor<F>(fun);
}


int main()
{
    int x[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    const int N = sizeof(x)/sizeof(int);
    vector<int> v(x, x+N);

    std::cout << "squaring each element in the array:" << std::endl;
    auto transformer = make_adaptor(square);
    std::copy(transformer(v.begin()), transformer(v.end()),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
 

    std::cout << "adding 3 to each element in the array:" << std::endl;
    auto transformer2 = make_adaptor(bind(add, placeholders::_1, 3));
    std::copy(transformer2(x), transformer2(x+N),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
 
 
    using boost::make_transform_iterator;
 
    std::cout << "adding 5 to each element in the array:" << std::endl;
    std::copy(  make_transform_iterator(x, bind(add, placeholders::_1, 5)), 
                make_transform_iterator(x+N, bind(add, placeholders::_1, 5)), 
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
 
}