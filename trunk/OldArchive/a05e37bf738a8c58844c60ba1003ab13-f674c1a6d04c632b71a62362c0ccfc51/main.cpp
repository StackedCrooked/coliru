#include <iostream>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#include <boost/ref.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
 
namespace fusion = boost::fusion;
 
template<typename T>
class Base
{
protected:
   int get_result() const{
      return static_cast<const T*>(this)->a;
   }
};
 
class TYPE_1 : public Base<TYPE_1>
{
   friend class Base<TYPE_1>;
   int a{1};
public:
   using Base<TYPE_1>::get_result;
};
 
class TYPE_2 : public Base<TYPE_2>
{
   friend class Base<TYPE_2>;
   int a{2};
public:
   using Base<TYPE_2>::get_result;
};
 
class TYPE_3 : public Base<TYPE_3>
{
   friend class Base<TYPE_3>;
   int a{3};
public:
   using Base<TYPE_3>::get_result;
};
 
struct Stateful
{
   int sum_result{0};
};
 
struct Iterater
{
   template<typename T>
   void operator()(Stateful& state, const T& t) const{
      state.sum_result += t.get_result();
   }
};
 
int main(){
 
   fusion::vector<TYPE_1, TYPE_2, TYPE_3> vec{TYPE_1(), TYPE_2(), TYPE_3()};
   Stateful state;
   fusion::for_each(vec, boost::bind<void>(Iterater(), boost::ref(state), _1));
   std::cout << state.sum_result << std::endl; //print 6
 
}