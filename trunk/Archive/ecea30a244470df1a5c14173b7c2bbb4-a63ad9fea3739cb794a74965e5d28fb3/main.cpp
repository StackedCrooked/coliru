#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <list>

int main()
{
    typedef std::list<int> L;
    L l(5);
    typedef L::const_iterator CI;
    typedef L::iterator I;
    CI cb = l.begin(), ce = l.end();
    I b = l.begin();

    std::transform(++cb, ce, ++b, std::bind2nd(std::plus<CI::value_type>(), 1));
    std::copy(l.begin(), l.end(), std::ostream_iterator<CI::value_type>(std::cout));
    std::cout<<std::endl;
    return 0;
}
