#include <iostream>
#include <memory>
#include <iterator>

namespace extstd {
    template <class E, class T, class Y, class D>
    std::basic_ostream<E, T>& operator<< (std::basic_ostream<E, T>& os,
    	                                  std::unique_ptr<Y, D> const& p) {
    	return os << p.get();
	}
 };

int main()
{
	using namespace extstd;

    std::ostream_iterator<std::unique_ptr<int>> os(std::cout);
    *os = std::unique_ptr<int>(new int);
}
