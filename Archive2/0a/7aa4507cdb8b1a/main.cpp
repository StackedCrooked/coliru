#include <iostream>
#include <memory>

namespace extstd {

    using namespace std;

    template <class E, class T, class Y, class D>
    basic_ostream<E, T>& operator<< (basic_ostream<E, T>& os,
    	                             unique_ptr<Y, D> const& p) {
    	return os << p.get();
	}
 };

int main()
{
	namespace std = extstd;

	std::unique_ptr<int> ptr(new int);
	std::cout << ptr;
}
