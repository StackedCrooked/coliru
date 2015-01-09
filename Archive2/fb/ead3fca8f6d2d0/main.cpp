#include <iostream>
#include <list>
#include <string>

#include <boost/assign.hpp>

struct AClass{
    AClass() {}
};

struct BClass{
    BClass() {}
};

struct AInfo{
    AInfo(std::string const& in, AClass const& a, BClass const& b)
       : infoname(in), m_nAClass(a), m_nBClass(b)
    { }
    
    std::string infoname;
    AClass m_nAClass;
    BClass m_nBClass;
};

int main() {
    typedef std::list<AInfo> listOfAInfo;

    listOfAInfo m_mlistOfAInfo =
        boost::assign::list_of
            ( AInfo ( "AInfoName1", AClass(), BClass() ))
            ( AInfo ( "AInfoName2", AClass(), BClass() ));
}
