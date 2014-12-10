#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/join.hpp>
#include <functional>
#include <iostream>
#include <vector>

using namespace boost::multi_index;

struct X
{
  int x,y;
};

std::ostream& operator<<(std::ostream& os,const X& a)
{
  return os<<"{"<<a.x<<","<<a.y<<"}";
}

typedef multi_index_container<
  X,
  indexed_by<
    ordered_non_unique<member<X,int,&X::x>>
  >
> multi_t;

struct view:std::vector<std::reference_wrapper<const X>>
{
  using base=std::vector<std::reference_wrapper<const X>>;

  template<typename InputIterator>
  view(InputIterator first,InputIterator last):base(first,last){}
  
  template<typename InputIterator>
  view(const std::pair<InputIterator,InputIterator> p):base(p.first,p.second){}  
};

int main()
{
  multi_t m={{0,1},{0,0},{0,2},{1,3},{1,1},{2,0},{2,1}};
  
  view v1=m.equal_range(0); // elements with x==0
  view v2=m.equal_range(2); // elements with x==2
  auto v3=boost::range::join(v1,v2); // join them
  boost::range::sort(v3,[](const X& a,const X& b){return a.y<b.y;}); // sort them by y
  for(const auto& x:v3)std::cout<<x<<" "; // output
}
