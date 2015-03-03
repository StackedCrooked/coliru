#include <string>
#include <vector>

class Base {
public:
    std::string Name;
};
using BaseList = std::vector<Base>;

class Derived : Base {
};
using DerivedList = std::vector<Derived>;

class BaseHandler {
public:
    void process( BaseList list ) {
    }
};

int main() {
 
    DerivedList list;
 
    BaseHandler bh;
    bh.process( list );
     
}