#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>



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
    A a(5);
    A b(42);
    A c(41);
    A d(42);
    A e(42);
    std::vector<A> vec;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    vec.push_back(d);
    
    boost::function<bool (A&)> f2 = boost::bind(fun,_1); //= ( boost::bind( &A::Is42, this, _1 ) );   
    int mycount = std::count_if (vec.begin(), vec.end(), boost::bind(&A::Is42,_1));
    std::cout<<"My Count:"<< mycount << std::endl; 
}
