#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>



struct A
{
  A(int val):d(val){};
  int d;
  bool Is42(){ return d==42; };
};

bool fun (A& a)
{
    return a.Is42();
}

 int main()
 {
    std::vector<A> vec;
    vec.push_back( A(5));
    vec.push_back( A(42));
    vec.push_back( A(41));
    vec.push_back( A(43));
    
    std::vector<A*> vecp;
    vecp.push_back(new A(5));
    vecp.push_back(new A(42));
    vecp.push_back(new A(42));
    
    std::vector<boost::shared_ptr<A> > vecsp;
    vecsp.push_back(boost::shared_ptr<A>(new A(5)));
    vecsp.push_back(boost::shared_ptr<A>(new A(42)));
    vecsp.push_back(boost::shared_ptr<A>(new A(42)));
    vecsp.push_back(boost::shared_ptr<A>(new A(42)));

    int mycount = std::count_if (vec.begin(), vec.end(), boost::bind(&A::Is42,_1));
    int mycount2 = std::count_if (vecp.begin(), vecp.end(), boost::bind(&A::Is42,_1));
    int mycount3 = std::count_if (vecsp.begin(), vecsp.end(), boost::bind(&A::Is42,_1));
    std::cout<<"My Count:"<< mycount << "\n" <<
               "My Count2:" << mycount2 << "\n" <<
               "My Count3:" << mycount3 << std::endl; 
}
