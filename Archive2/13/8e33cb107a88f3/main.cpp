#include <iostream>
#include <memory>

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

	std::unique_ptr<int> ptr(new int);
	std::cout << ptr;
}
