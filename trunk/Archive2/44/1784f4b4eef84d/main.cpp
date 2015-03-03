#include <string>
#include <vector>
#include <memory>

class Base {
public:
    std::string Name;
};
using BaseList = std::vector<std::shared_ptr<Base>>;

class Derived : Base {
};
using DerivedList = std::vector<std::shared_ptr<Derived>>;

class BaseHandler {
public:
    void process( BaseList list ) {
    }
};

int main() {
 
    BaseList list;
 
    BaseHandler bh;
    bh.process( list );
     
}