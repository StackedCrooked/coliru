#include <algorithm>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <functional>

using namespace boost::multi_index;

#include <iosfwd>

template<typename T,typename Q>
struct pair_
{
  T first;
  Q second;
};

namespace std{
    
template<typename T,typename Q>
struct less<pair_<T,Q>>
{
  using subcompare=std::function<bool(const pair_<T,Q>&,const pair_<T,Q>&)>;
  subcompare subcmp;

  bool operator()(const pair_<T,Q>& x,const pair_<T,Q>& y)const
  {
     if(x.first<y.first)return true;
     if(y.first<x.first)return false;
     if(subcmp)         return subcmp(x,y);
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
    ordered_non_unique<
      identity<pair_<T,Q>>,
      std::reference_wrapper<const std::less<pair_<T,Q>>>>
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
  std::less<pair_<std::string,int>> less;
  list_multimap<std::string,int>    lmm{boost::make_tuple(
                                      boost::make_tuple(),
                                      boost::make_tuple(
                                        identity<pair_<std::string,int>>{},
                                        std::cref(less)
                                      )
                                    )};
  auto&                             mm=lmm.get<1>();
  
  lmm={{"A",1},{"B",2},{"A",3},{"C",4},{"B",5},{"C",6},{"A",7}};
  std::cout<<lmm<<"\n";
  
  // list values with key "A"

  auto r=mm.equal_range("A");
  std::for_each(r.first,r.second,[](const auto& x){std::cout<<x<<" ";});
  std::cout<<"\n";
  
  // replace (C,4) with (B,8)
  
  std::less<pair_<std::string,int>>::subcompare subcmp=
  [&](const auto&x, const auto& y){
    return lmm.iterator_to(x)<lmm.iterator_to(y);
  };
  
  r=mm.equal_range("C");
  auto it=std::find_if(r.first,r.second,[](const auto& x){return x.second==4;});
  less.subcmp=subcmp;
  mm.modify(it,[&](auto& x){x={"B",8};});
  less.subcmp=nullptr;
  std::cout<<lmm<<"\n";

  // list values with key "B"

  r=mm.equal_range("B");
  std::for_each(r.first,r.second,[](const auto& x){std::cout<<x<<" ";});
  std::cout<<"\n";  
}
