#include <boost/phoenix.hpp>
#include <algorithm>
#include <map>

namespace phx = boost::phoenix;

struct pair_first_impl
{
   template<class TPair> struct result { typedef typename TPair::first_type const& type; };

   template<class TPair>
   typename TPair::first_type const& operator() (TPair const& pair) const {
      return pair.first;
   }

   template<class TPair>
   typename TPair::first_type& operator() (TPair& pair) {
      return pair.first;
   }
};

static phx::function<pair_first_impl> pair_first;


void test1()
{
   using phx::placeholders::_1;

   std::map<int, std::string> mymap;
   std::find_if(mymap.begin(), mymap.end(), pair_first(_1) == 1);
}

void test2()
{
   using Pair = std::pair<const int, std::string>;
   using namespace phx::arg_names;

   std::map<int, std::string> mymap;
   std::find_if(mymap.begin(), mymap.end(), phx::bind(&Pair::first, arg1) == 1);
}

void test3()
{
   std::map<int, std::string> mymap;
   using Pair = decltype(mymap)::value_type;
   using namespace phx::arg_names;

   std::find_if(mymap.begin(), mymap.end(), phx::bind(&Pair::first, arg1) == 1);
}

int main()
{
    test1();
    test2();
    test3();
}
