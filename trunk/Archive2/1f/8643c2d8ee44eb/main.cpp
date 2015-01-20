#include <iostream>
#include <vector>

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

int main() {
	std::vector<int> a;
    
    for(int i = 0; i < 10; ++i)
        a.push_back(i);
        
    /*
    std::cout << "[";
    for(unsigned int i = 0; i < a.size(); ++i) {
        std::cout << " " << a[i];
    }
    std::cout << "]";
    */
    
    std::cout << a << std::endl;
    
    return 0;
}
