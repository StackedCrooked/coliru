#include <boost/optional.hpp>

class myint {
public:
    int m_a;
    myint (int r_a) : m_a(r_a) {}
};

struct myclass {
    boost::optional<myint> content;
    
    myclass(const boost::optional<myint>& a) :content(a) {}
};


struct myprotectedclass {
    boost::optional<myint> content;
    
    myprotectedclass(const boost::optional<myint>& a) :content((const boost::optional<myint>&)(a)) {}
};


int main() { 
    
     myclass a(0);
     if (a.content) std::cout << "This should not be happing" << std::endl;
     else std::cout << "Vanilla code has a bug" << std::endl;
   
     /*
     //this one is a compile error
     myclass aa(1);
     if (aa.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     */
     
     myprotectedclass b(0);
     if (b.content) std::cout << "This should not be happing" << std::endl;
     else std::cout << "Solution has no bug, note that compilation error is acceptable as well for this case" << std::endl;
    
     /*
     //this one is a compile error too but that is less surprising
     myprotectedclass bb(1);
     if (bb.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     */
    
     
     std::cout << "Further tests:" << std::endl;
     
     myprotectedclass c(boost::none);
     if (!c.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     

     myprotectedclass d(myint(0));
     if (d.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     myprotectedclass e(myint(1));
     if (e.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     boost::optional<myint> foobar = boost::none;
     myprotectedclass f(foobar);
     if (!f.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     boost::optional<myint> bar = myint(0);
     myprotectedclass g(bar);
     if (g.content) std::cout << "correct ";
     else std::cout << "incorrect ";

     boost::optional<myint> foo = myint(1);
     myprotectedclass h(foo);
     if (h.content) std::cout << "correct ";
     else std::cout << "incorrect ";
     
    

}