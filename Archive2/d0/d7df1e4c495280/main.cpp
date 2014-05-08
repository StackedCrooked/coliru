#include <boost/spirit/include/karma.hpp>
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
        if (sharedPtrList.empty())
            return {};

        std::string result;
        result.reserve(20 * sharedPtrList.size()); // average length preallocate?

        auto out = back_inserter(result);

        using namespace boost::spirit::karma;
        for(auto& b : sharedPtrList)
            generate(out, string << ':' << string << ',', b->string1(), b->string2());

        result.resize(result.size()-1);
        return result; // moves
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
