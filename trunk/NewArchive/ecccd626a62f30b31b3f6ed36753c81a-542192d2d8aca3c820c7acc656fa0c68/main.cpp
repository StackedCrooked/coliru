#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

typedef float mytype;

template<class T>
class foo {
    public:
        void blah(int j){
            std::cout << j;    
        }
        void(foo::*aliasf)(int) = &foo::blah;
};

struct cleanfoo{
    boost::shared_ptr<foo<mytype> > b;
    cleanfoo(){
        b = boost::make_shared<foo<mytype> >();   
    }
    ~cleanfoo(){
        b.reset();   
    }
};

int main() {
    
    cleanfoo cfoo;
    ((cfoo.b)-> blah)(5);
    //(((cfoo.b).*aliasf))(5);

    (((*cfoo.b).*(cfoo.b->aliasf)))(5);


}