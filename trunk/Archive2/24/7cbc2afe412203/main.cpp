#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <ext/functional>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>

bool even(int n) { return n%2==0; }
int main()
{
    // note: must be defined at file scope before C++11
    struct Even {
        bool operator()(int n) const {
            return n%2==0;
        }
    };


    std::vector<int> vec = {1,2,3,4,5,6,7};

    // pointer to function (could also write &even to be explicit)
    std::cout << std::count_if(vec.begin(),vec.end(), even) << '\n';

    // user-defined function object
    std::cout << std::count_if(vec.begin(),vec.end(), Even() ) << '\n';

    // STL (non-standard C++)
    std::cout << std::count_if(vec.begin(),vec.end(),
                  __gnu_cxx::compose1(
                       std::bind2nd(std::equal_to<int>(),0),
                       std::bind2nd(std::modulus<int>(),2)
                   )
                 ) << '\n';

    // C++11 lambda
    std::cout << std::count_if(vec.begin(),vec.end(),
                               [](int n){return n%2==0;}) << '\n';

    // boost.phoenix (replaced boost.lambda)
    using boost::phoenix::arg_names::arg1;
    std::cout << std::count_if(vec.begin(),vec.end(), arg1%2 == 0 );
}
