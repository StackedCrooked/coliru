#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

struct Elem{
    double trae;
    unsigned int coeff;
};

template <typename Elem>
struct HaveEqualAngularCoefficient : public std::binary_function<bool, Elem, Elem>{
    bool operator()(const Elem& lhs, const Elem& rhs){   
        return (lhs.coeff == rhs.coeff);
    }
};

template <typename C>
void makeCompound(C& container){
    typedef typename C::value_type Elem;
    typename C::iterator begin = container.begin();
    typename C::iterator end = container.end();
    typename C::iterator it = begin; 
    
    while( (it != end) ){
        it = std::adjacent_find(it, end, HaveEqualAngularCoefficient<Elem>() );
        if(it == end)
            break;
        typename C::iterator tmp = it;
        std::advance(tmp, 1); 
        it->trae += tmp->trae;
        container.erase(tmp);
    }
}

template <typename C>
std::ostream& operator << ( std::ostream& stream, const C& container ){
    for(typename C::const_iterator it = container.begin(); it != container.end(); ++it){
        stream  << it->trae  << std::endl;
        stream << it->coeff << std::endl;
        stream << endl;
    }
    stream << endl;
    return stream;
}

int main() {
    using namespace std;
    
    Elem one{1, 1};
    Elem two{1, 2};
    Elem three{1, 2};
    Elem four{1, 2};
    Elem five{1, 1};
    Elem six{1, 2};
    Elem seven{1, 2};
    
    std::list<Elem> l;
    l.push_back(one);
    l.push_back(two);
    l.push_back(three);
    l.push_back(four);
    l.push_back(five);
    l.push_back(six);
    l.push_back(seven);
    
    cout << l << endl;
    
    makeCompound(l);
    
    cout << l << endl;

}
