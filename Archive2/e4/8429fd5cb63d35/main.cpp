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

int main() {
    typedef std::map<int, AInfo> listOfAInfo;

    listOfAInfo m_mlistOfAInfo =
        boost::assign::map_list_of
            ( 1, AInfo { "AInfoName1", AClass(), BClass() })
            ( 2, AInfo { "AInfoName2", AClass(), BClass() });
}
