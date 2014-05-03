#include <string>
#include <sstream>
#include <vector>
#include <boost/variant.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <iostream>

struct TypeA { int         varA; int         varB; };
struct TypeB { std::string varA; std::string varB; };

typedef boost::variant<TypeA, TypeB> MyVariantType;

struct MyCommandVisitor : boost::static_visitor<> {
    void operator()(TypeA const& t, std::stringstream& os, int& sum, int& /*charCount*/) const {
        sum += t.varA;
        os << "TYPEA ACTION: " << t.varB << std::endl;
    }

    void operator()(TypeB const& t, std::stringstream& os, int& /*sum*/, int& charCount) const {
        charCount += t.varA.size();
        os << t.varB << " ACTION " << t.varA << std::endl;
    }

    static std::string emitWork(std::vector<MyVariantType> const listOfVariants) {
        int sum = 0, charCount = 0;
        std::stringstream os;
        BOOST_FOREACH(MyVariantType const& v, listOfVariants) {
            boost::apply_visitor(boost::bind(MyCommandVisitor(), _1, boost::ref(os), boost::ref(sum), boost::ref(charCount)), v);
        }
        return os.str();
    }
}; //End class MyCommandVisitor

int main() {
    TypeA const ta { 1, 2 };
    TypeB const tb { "String1", "String2" };

    std::cout << "Result:\n" << MyCommandVisitor::emitWork({ ta, tb }) << "\n";
}
