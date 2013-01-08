#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>

template<typename Container, typename F>
auto max(Container const & c, F && pred) -> decltype(*std::begin(c))
{  
    if ( std::begin(c) == std::end(c) ) 
        throw std::invalid_argument("empty container is not allowed.");

    typedef decltype(*std::begin(c)) V;
    auto cmp = [&](V a, V b){ return pred(a) < pred(b); };
    return *std::max_element(std::begin(c), std::end(c), cmp);
}
 
 namespace test
 {
     template<size_t N>
     struct intcollection
     {
         int _data[N];
 
      int * begin() { return _data; }
         int * end() { return _data + N; }

         int const * begin() const { return _data; }
         int const * end() const { return _data + N; }
     };
 }
 
int main()
{
    std::vector<int> v = {1,43,10,17};
    auto m = max(v, [](int x) { return -1 * std::abs(42-x); });
    std::cout << m << std::endl;
    
    int l[] = {1,43,10,17}; //works with array also!
    auto a = max(l, [](int x) { return -1 * std::abs(42-x); });
    std::cout << a << std::endl;
    
    test::intcollection<4> c{{1,43,10,17}}; //works with user-defined container also!
    auto r = max(c, [](int x) { return -1 * std::abs(42-x); });
    std::cout << r << std::endl;
}
