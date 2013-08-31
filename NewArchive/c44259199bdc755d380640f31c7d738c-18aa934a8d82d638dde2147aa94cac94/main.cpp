#include <boost/optional.hpp>

class myint {
public:
    int m_a;
    myint (int r_a) : m_a(r_a) {}
};

boost::optional<myint> myintctor(int arg) {return myint(arg);}
boost::optional<myint> myintctor(boost::none_t arg) {return arg;}

struct myclass {
    boost::optional<myint> content0;
    boost::optional<myint> content1;
    boost::optional<myint> content2;
    
    template<class T0, class T1, class T2>
    myclass(const T0& a0, const T1& a1, const T2& a2) 
    :content0(myintctor(a0)), content1(myintctor(a1)), content2(myintctor(a2))
    {}
};

int main() {
     myclass a(0, boost::none, 1);
     if (a.content0) std::cout << "exists ";
     else std::cout << "noexists ";
     if (a.content1) std::cout << "exists ";
     else std::cout << "noexists ";
     if (a.content2) std::cout << "exists ";
     else std::cout << "noexists ";
}