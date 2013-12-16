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

template <class C, class F>
class iterator_adaptor {
    
    F func;

public:
    iterator_adaptor( F f ) : func(f) {   }
    
    boost::transform_iterator<F, typename C::iterator> operator() (const typename C::iterator it) {
        return boost::make_transform_iterator(it, func);  
    }

};

template <typename C, typename F>
iterator_adaptor<C,F> make_adaptor( C , F fun ) {
    return iterator_adaptor<C, F>(fun);
}

template <class F>
class iterator_adaptor2 {
    
    F func;

public:
    iterator_adaptor2( F f ) : func(f) {   }
    
    template<typename Iter>
    boost::transform_iterator<F, Iter> operator() (Iter it) {
        return boost::make_transform_iterator(it, func);  
    }

};

template <typename F>
iterator_adaptor2<F> make_adaptor( F fun ) {
    return iterator_adaptor2<F>(fun);
}


int main()
{
    int x[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    const int N = sizeof(x)/sizeof(int);
    vector<int> v(x, x+N);

    typedef std::binder1st< std::multiplies<int> > Function;
    typedef boost::transform_iterator<Function, int*> doubling_iterator;
    
    doubling_iterator i    (  x,   std::bind1st(std::multiplies<int>(), 2));
    doubling_iterator i_end(x + N, std::bind1st(std::multiplies<int>(), 2));

    typedef int (*Function2)(int);
    typedef boost::transform_iterator<Function2, int*> squaring_iterator;
    
    squaring_iterator isq    (  x,   square);
    squaring_iterator isq_end(x + N, square);

    std::cout << "multiplying the array by 2:" << std::endl;
    while (i != i_end)
      std::cout << *i++ << " ";
    std::cout << std::endl;
    
    std::cout << "adding 4 to each element in the array:" << std::endl;
    std::copy(boost::make_transform_iterator(  x,   std::bind1st(std::plus<int>(), 4)),
              boost::make_transform_iterator(x + N, std::bind1st(std::plus<int>(), 4)),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "squaring each element in the array:" << std::endl;
    std::copy(isq, isq_end,
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;


    std::cout << "again, squaring each element in the array:" << std::endl;
    auto transformer = make_adaptor(v, square);
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