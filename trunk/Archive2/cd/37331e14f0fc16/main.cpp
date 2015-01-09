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
    std::string infoname;
    AClass m_nAClass;
    BClass m_nBClass;
};

namespace {
    AInfo make_a(std::string const& in, AClass const& a, BClass const& b) {
        AInfo r = { in, a, b };  // or using memberwise assignments
        return r; 
    }
}

int main() {
    typedef std::list<AInfo> listOfAInfo;

    listOfAInfo m_mlistOfAInfo =
        boost::assign::list_of
            ( make_a( "AInfoName1", AClass(), BClass() ))
            ( make_a( "AInfoName2", AClass(), BClass() ));
}
