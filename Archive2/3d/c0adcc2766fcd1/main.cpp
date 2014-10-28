#include <iostream>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/for_each.hpp>

struct A
{
   int ivalue;
   double dvalue;
   std::string svalue;
};

BOOST_FUSION_ADAPT_STRUCT(
      A,
      (int, ivalue)
      (double, dvalue)
      (std::string, svalue)
)

struct assigner
{
public:
   assigner(void** pars) :
      counter(0), params(pars)
   {
   }
   template<typename T>
   void operator () (T& t) const
   {
      t = *static_cast<T*>(*(params + counter));
      ++counter;
   }
private:
   mutable int counter;
   void** params;
};

A create_from_params(void* params[])
{
   A object;
   boost::fusion::for_each(object, assigner(params));
   return object;
}

int main()
{
   int ivalue = 1;
   double dvalue = 2.0;
   std::string svalue = "this";

   void* params[] = {&ivalue, &dvalue, &svalue};
   A object = create_from_params(params);
   std::cout << object.ivalue << " " << object.dvalue << " " << object.svalue << std::endl;
}
