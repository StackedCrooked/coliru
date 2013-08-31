#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>

typedef std::list<double> container;
typedef container::const_iterator const_iter;

double median(container l) {
    typedef container::size_type l_sz;
	
	l_sz size = l.size();
	if (size == 0)
		throw std::domain_error("median of an empty list");
	
	l.sort();

    std::size_t mid = size / 2;
    const_iter it = l.begin();
    
    for(std::size_t i = 0; i != mid; ++i) {
        ++it;
    }
    
    if (size % 2 == 0) {
        const_iter base = it--;
        return (*base + *it) / 2;
    }
    else {
        return *it;
    }
}

int main()
{
    container c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    //c.push_back(4);
    std::cout << median(c) << std::endl;
}
