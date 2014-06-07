#include <iostream>
    
//OPTION A 
#include <bitset>
#include <utility>  


#define CONCAT2(X,Y) X##Y
#define CONCAT(X,Y) CONCAT2(X,Y)
#define DEFINE(NAME,NUMFIELDS) struct NAME { \
    std::bitset<NUMFIELDS> mask_; 
#define MEMBER(INDEX,TYPE,NAME) TYPE NAME; \
    using CONCAT(NAME,_bit) = std::integral_constant<int,INDEX>; \
    TYPE const& CONCAT(get,NAME) () const {return NAME;} \
    void CONCAT(set,NAME) (TYPE const& v_) {NAME=v_; mask_.set(INDEX);}
#define ENDDEFINE() };

DEFINE(mypodA,3)
MEMBER(0,std::string,first)
MEMBER(1,std::string,last)
MEMBER(2,long,salary)
ENDDEFINE()

void A() {
    mypodA a;
    a.setfirst("HI");
    std::cout << a.getfirst() << a.mask_.test(mypodA::first_bit{}) << a.mask_.test(mypodA::last_bit{}) << '\n';
}
        
        
        
//OPTION B
#include <boost/optional.hpp>
struct mypodB {
    boost::optional<std::string> first;
    boost::optional<std::string> last;
    boost::optional<long> salary;
};

void B() {
    using boost::type_traits::no_type;
    mypodB b;
    b.first = "HI";
    std::cout << b.first.get() << b.first << b.last << '\n';
}




int main() {
    A();
    B();
}