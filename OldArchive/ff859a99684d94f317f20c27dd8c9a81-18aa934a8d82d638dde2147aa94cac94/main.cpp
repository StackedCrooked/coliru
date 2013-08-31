#include <boost/optional.hpp>

class myint {
public:
    int m_a;
    myint (int r_a) : m_a(r_a) {}
};

boost::optional<myint> myintctor(boost::none_t arg) {return arg;}
boost::optional<myint> myintctor(const myint& arg) {return myint(arg);}

struct myclass {
    boost::optional<myint> content;
    
    template<class T0>
    myclass(const T0& a0) :content(myintctor(a0))
    {}
};

int main() { 
     myclass a(0);
     if (a.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     
     myclass b(boost::none);
     if (!b.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     
     myclass c(1);
     if (c.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     myclass d(myint(0));
     if (d.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     myclass e(myint(1));
     if (e.content) std::cout << "correct ";
     else std::cout << "incorrect ";

}