#include <vector>
#include <sstream>
#include <boost/make_shared.hpp>

struct B
{ 
    typedef boost::shared_ptr<const B> ConstPtr;
    std::string string1() const { return "string1"; }
    std::string string2() const { return "string2"; }
};

struct A
{
    std::vector<B::ConstPtr> sharedPtrList;
    /***code***/
    std::string returnConcatString() const {
        std::ostringstream os;
        for(auto& b : sharedPtrList)
            os << b->string1() << ':' << b->string2() << ',';

        auto s = os.str();
        if (!s.empty())
            s.resize(s.size()-1);
        return s; // moves
    }
};

#include <iostream>

int main()
{
    A a;

    std::cout << "'" << a.returnConcatString() << "'\n";

    a.sharedPtrList.push_back(boost::make_shared<B>());
    std::cout << "'" << a.returnConcatString() << "'\n";
}
