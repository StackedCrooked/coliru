#include <algorithm>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <functional>

using namespace boost::multi_index;

#include <iosfwd>

template<typename T,typename Q>
struct pair_
{
  T first;
  Q second;
  
  using compare=std::function<bool(const pair_&,const pair_&)>;
  mutable compare* subcmp;
  
  pair_(const T& first,const Q& second,compare* subcmp=nullptr):
    first(first),second(second),subcmp(subcmp){}
};

namespace std{
    
template<typename T,typename Q>
struct less<pair_<T,Q>>
{
  bool operator()(const pair_<T,Q>& x,const pair_<T,Q>& y)const
  {
     if(x.first<y.first)return true;
     if(y.first<x.first)return false;
     if(x.subcmp)       return (*x.subcmp)(x,y);
     if(y.subcmp)       return (*y.subcmp)(x,y);
     return false;
  }
  
  template<typename R>
  bool operator()(const R& x,const pair_<T,Q>& y)const
  {
     return x<y.first;
  }
  
  template<typename R>
  bool operator()(const pair_<T,Q>& x,const R& y)const
  {
     return x.first<y;
  }
};

} // namespace std

template<typename T,typename Q>
std::ostream& operator<<(std::ostream& os,const pair_<T,Q>& p)
{
  return os<<"("<<p.first<<","<<p.second<<")";
}

template<typename T,typename Q>
using list_multimap=multi_index_container<
  pair_<T,Q>,
  indexed_by<
    random_access<>,
    ordered_non_unique<identity<pair_<T,Q>>>
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
  
  // list values with key "A"

  auto r=mm.equal_range("A");
  while(r.first!=r.second)std::cout<<*(r.first)++<<" ";
  std::cout<<"\n";
  
  // replace (C,4) with (B,8)
  
  pair_<std::string,int>::compare subcmp=[&](const auto&x, const auto& y){
    auto itx=lmm.iterator_to(x);
    auto ity=lmm.iterator_to(y);
    return itx<ity;
  };
  
  r=mm.equal_range("C");
  auto it=std::find_if(r.first,r.second,[](const auto& x){return x.second==4;});
  mm.modify(it,[&](auto&x){x={"B",8,&subcmp};});
  it->subcmp=nullptr;
  std::cout<<lmm<<"\n";

  // list values with key "B"

  r=mm.equal_range("B");
  while(r.first!=r.second)std::cout<<*(r.first)++<<" ";
  std::cout<<"\n";  
}
