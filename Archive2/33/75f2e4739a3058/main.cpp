#include <iostream>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/deref.hpp>

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

template<typename Next, typename Last>
struct print_struct
{
   static void apply(Next current)
   {
      std::cout << boost::fusion::deref(current) << std::endl;
      print_struct<typename boost::fusion::result_of::next<Next>::type, Last>::apply(boost::fusion::next(current));
   }
};

template<typename Last>
struct print_struct<Last, Last>
{
   static void apply(Last)
   {
   }
};

template<typename Seq>
void print(const Seq& seq)
{
   print_struct<typename boost::fusion::result_of::begin<const Seq>::type, typename boost::fusion::result_of::end<const Seq>::type>::
      apply(boost::fusion::begin(seq));
}


int main()
{
   Foo f = {1, 2};
   print(f);
}
