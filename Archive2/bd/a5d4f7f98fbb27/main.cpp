#include <map>
#include <iostream>

template <typename K, typename V, typename W>
void map_insert(std::map<K,V>& m, const K& k, W&& v) 
{m.emplace(std::piecewise_construct,std::forward_as_tuple(k),std::forward_as_tuple(std::forward<W>(v)));}

template <typename K, typename V, typename W>
void map_insert(std::map<K,V>& m, K& k, W&& v) 
{m.emplace(std::piecewise_construct,std::forward_as_tuple(k),std::forward_as_tuple(std::forward<W>(v)));}

template <typename K, typename V, typename W>
void map_insert(std::map<K,V>& m, K&& k, W&& v) 
{m.emplace(std::piecewise_construct,std::forward_as_tuple(std::move(k)),std::forward_as_tuple(std::forward<W>(v)));}

struct announcer {
    announcer():val(0.0){std::cout<<"def ctor"<<val<<"\n";}
    announcer(const announcer&r):val(r.val){std::cout<<"cpy ctor"<<val<<"\n";}
    announcer(announcer&&r):val(r.val){std::cout<<"mov ctor"<<val<<"\n";}
    announcer(double v):val(v){std::cout<<"cnv ctor"<<val<<"\n";}
    announcer&operator=(const announcer&r){val=r.val;std::cout<<"cpy ctor"<<val<<"\n";return *this;}
    announcer&operator=(announcer&&r){val=r.val;std::cout<<"mov ctor"<<val<<"\n";return *this;}
    announcer&operator=(double v){val=v;std::cout<<"cnv ctor"<<val<<"\n";return *this;}
    ~announcer(){std::cout<<"dtor"<<val<<"\n";}
    bool operator<(const announcer&r)const{return val<r.val;}
    double val;
};

int main() {
  std::map<announcer,announcer>m1;
  std::cout<<"checkpoint A\n";
  map_insert(m1, announcer(1.0), announcer(2.0));
  std::cout<<"checkpoint B\n";
  map_insert(m1, announcer(3.0), 4.0);
  std::cout<<"checkpoint C\n";
  //map_insert(m1, 5.0, announcer(6.0));//error: no matching function for call to 'map_insert(std::map<announcer, announcer>&, double, announcer)'
  std::cout<<"map size="<<m1.size()<<'\n';
}