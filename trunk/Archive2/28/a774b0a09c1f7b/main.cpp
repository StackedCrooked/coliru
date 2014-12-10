#include <iostream>
#include <memory>

namespace ext {
    template <class E, class T, class Y, class D>
    std::basic_ostream<E, T>& operator<< (std::basic_ostream<E, T>& os,
    	                             std::unique_ptr<Y, D> const& p) {
    	return os << p.get();
	}
}

namespace extstd {
    using namespace std;
    using namespace ext;
}

int main()
{
    namespace std = extstd;
    using namespace ext;
    
	std::unique_ptr<int> ptr(new int);
	std::cout << ptr;
    std::operator << ( std::cout, ptr );
}
