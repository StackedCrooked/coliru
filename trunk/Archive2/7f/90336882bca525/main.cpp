    #include <bitset>
    #include <utility>

    #define CONCAT2(X,Y) X##Y
    #define CONCAT(X,Y) CONCAT2(X,Y)
    #define DEFINE(NAME,NUMFIELDS) struct mypod { \
        std::bitset<NUMFIELDS> mask_; 
    #define MEMBER(INDEX,TYPE,NAME) TYPE NAME; \
        using CONCAT(NAME,_bit) = std::integral_constant<int,INDEX>; \
        TYPE const& CONCAT(get,NAME) () const {return NAME;} \
        void CONCAT(set,NAME) (TYPE const& v_) {NAME=v_; mask_.set(INDEX);}
    #define ENDDEFINE() };

    DEFINE(mypod,3)
    MEMBER(0,std::string,first)
    MEMBER(1,std::string,last)
    MEMBER(2,long,salary)
    ENDDEFINE()
    
    #include <iostream>
    int main() {
        mypod a;
        a.setfirst("HI");
        std::cout << a.getfirst() << a.mask_.test(mypod::first_bit{}) << a.mask_.test(mypod::last_bit{});
    }
        