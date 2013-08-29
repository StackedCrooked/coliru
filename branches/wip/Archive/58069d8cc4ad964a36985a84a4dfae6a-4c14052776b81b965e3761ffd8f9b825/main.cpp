#include <iostream>

using namespace std;

template<typename Trait>
class XmlUtil {
    //I don't know if those are better declared to be public, it depends on your
    //design
    typedef typename Trait::type T;
    typedef typename Trait::func1 func1;
    typedef typename Trait::func2 func2;
    
    //use T, func1 and func2 normally here
}; 

template <typename T>
struct Trait{
    typedef T type;
    typedef T (*func1)(const T&, const string&);
    typedef string (*func2)(const T&);
};

//As you can see nothing depends on XmlType, that's why I'm declaring it so late
class XmlType;
typedef XmlUtil<Trait<XmlType> > MyXmlUtil;

class Whatever;
typedef XmlUtil<Trait<Whatever> > MyXmlUtilWhatever;

int main(){ }
