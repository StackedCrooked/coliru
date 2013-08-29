#include <iostream>

using namespace std;

template<typename Trait>
class XmlUtil {
    typedef typename Trait::type T;
    typedef typename Trait::func1 func1;
    typedef typename Trait::func2 func2;
    
}; 

class XmlType;

XmlType XmlType_(const XmlType& a, const string& b);
string XmlType_(const XmlType& a);

template <typename T>
struct Trait{
    typedef T type;
    typedef T (*func1)(const T&, const string&);
    typedef string (*func2)(const T&);
};

typedef XmlUtil<Trait<XmlType> > MyXmlUtil;

int main(){ 
}
