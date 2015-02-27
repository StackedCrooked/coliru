#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>

using namespace boost::multi_index;

#include <iosfwd>

template<typename T,typename Q>
struct pair_
{
  T first;
  Q second;
};

template<typename T,typename Q>
std::ostream& operator<<(std::ostream& os,const pair_<T,Q>& p)
{
  return os<<"("<<p.first<<","<<p.second<<")";
}

template<typename T,typename Q>
using list_multimap=multi_index_container<
  pair_<T,Q>,
  indexed_by<
    sequenced<>,
    ordered_non_unique<
      composite_key<
        pair_<T,Q>,
        member<pair_<T,Q>,T,&pair_<T,Q>::first>,
        member<pair_<T,Q>,Q,&pair_<T,Q>::second>
      >
    >
  >
>;

template<typename T,typename Q>
std::ostream& operator<<(std::ostream& os,const list_multimap<T,Q>& lmm)
{
   for(const auto& p:lmm)os<<p<<" ";
   return os;
}

#include <string>
#include <iostream>

int main()
{
  list_multimap<std::string,int> lmm{{"A",1},{"B",2},{"A",3},{"C",4},{"B",5},{"C",6},{"A",7}};
  auto&                          mm=lmm.get<1>();

  std::cout<<lmm<<"\n";
  
  // List values with key "A"

  auto r=mm.equal_range("A");
  while(r.first!=r.second)std::cout<<*(r.first)++<<" ";
  std::cout<<"\n";
  
  // replace (C,4) with (B,8)
  
  mm.replace(mm.find(std::make_tuple("C",4)),{"B",8});
  std::cout<<lmm<<"\n";
  
  // List values with key "B"

  r=mm.equal_range("B");
  while(r.first!=r.second)std::cout<<*(r.first)++<<" ";
  std::cout<<"\n";
}
