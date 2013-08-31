#include <boost/optional.hpp>

class myint {
public:
    int m_a;
    myint (int r_a) : m_a(r_a) {}
};

boost::optional<myint> inline myintctor(boost::optional<myint> arg) {return arg;}

struct myclass {
    boost::optional<myint> content;
    
    template<class T0>
    myclass(const T0& a) :content(myintctor(a))
    {}
};

int main() { 
    
    /*
     // now this is a compile error
     myclass a(0);
     if (a.content) std::cout << "correct ";
     else std::cout << "incorrect ";
    */
   
    
    /*
     //this one is a compile error too but that is less surprising
     myclass c(1);
     if (c.content) std::cout << "correct ";
     else std::cout << "incorrect ";
    */
     
     myclass b(boost::none);
     if (!b.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     

     myclass d(myint(0));
     if (d.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     myclass e(myint(1));
     if (e.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     boost::optional<myint> foobar = boost::none;
     myclass h(foobar);
     if (!h.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     boost::optional<myint> bar = myint(0);
     myclass g(bar);
     if (g.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     boost::optional<myint> foo = myint(1);
     myclass f(foo);
     if (f.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     
    

}