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
  int GetValue() { return this->d; };
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
    
    int counter=0;
    for (std::vector<A>::iterator it = vec.begin(); it!=vec.end(); ++it)
    {
        if (it->Is42())
            counter++;
    }
    

    int mycount = std::count_if (vec.begin(), vec.end(), boost::bind(&A::Is42,_1));
    int mycount2 = std::count_if (vecp.begin(), vecp.end(), boost::bind(&A::Is42,_1));
    int mycount3 = std::count_if (vecsp.begin(), vecsp.end(), boost::bind(&A::Is42,_1));
    int mycount4 = std::count_if (vec.begin(), vec.end(), (boost::bind(&A::GetValue,_1)==42) || (boost::bind(&A::GetValue,_1)==5) );
    std::cout<<"For loop Count:"<< counter << "\n" <<
               "My Count:"<< mycount << "\n" <<
               "My Count2:" << mycount2 << "\n" <<
               "My Count3:" << mycount3 << "\n" <<
               "My Count4:" << mycount4 << std::endl; 
}
