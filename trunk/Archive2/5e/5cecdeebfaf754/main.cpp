#include <iostream>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/for_each.hpp>

struct Foo
{
   int a;
   int b;
};

BOOST_FUSION_ADAPT_STRUCT(
      Foo,
      (int, a)
      (int, b)
);

struct print_s 
{ 
   template<typename T>
   void operator () (const T& arg) const
   {
      std::cout << arg << std::endl;
   } 
};

template<typename Seq>
void print(const Seq& seq)
{
   boost::fusion::for_each(seq, print_s());
}


int main()
{
   Foo f = {1, 2};
   print(f);
}

