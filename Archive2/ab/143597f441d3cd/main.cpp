#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename Elem>
struct makeCompoundHelper : public std::binary_function<bool, Elem, Elem>{
    bool operator()(const Elem& lhs, const Elem& rhs){   
        return (lhs.coeff == rhs.coeff);
    }
    static void exec(Elem& lhs, const Elem& rhs){
        lhs.trae += rhs.trae;
    }
};

template <typename C>
void makeCompound(C& container){
    typedef makeCompoundHelper<typename C::value_type> Helper;
    typename C::iterator begin = container.begin();
    typename C::iterator end = container.end();
    typename C::iterator it = begin; 
    
    while( it != end ){
        it = std::adjacent_find(it, end, Helper() );
        if(it == end)
            break;
        typename C::iterator next = it;
        std::advance(next, 1); 
        Helper::exec(*it, *next);
        container.erase(next);
    }
}

struct Elem{
    double trae;
    unsigned int coeff;
};

template <typename Stream, typename C>
Stream& operator << ( Stream& stream, const C& container ){
    for(typename C::const_iterator it = container.begin(); it != container.end(); std::advance(it, 1)){
        stream  << "(" << it->trae  << ", " <<  it->coeff << ")";
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
    Elem six{1, 3};
    Elem seven{1, 3};
    
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
