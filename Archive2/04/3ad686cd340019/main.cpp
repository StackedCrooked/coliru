#include <map>
#include <utility>
#include <type_traits>
#include <functional>
#include <iostream>

template <typename T, typename C = std::less<T>>
struct Cmp
{    
    template <typename U, typename W>
    bool operator()(U u, W w) const
    {
        static_assert(std::is_same<U, T>::value && std::is_same<W, T>::value, "Type mismatch");        
        return c(u, w);
    }
    C c;
};

int main()
{
  std::map<int,float,Cmp<int>> m1;
  
  m1.insert(std::pair<int,float>(10,15.0f));   //step-1
  //m1.insert(std::pair<float,int>(12.0f,13));   //step-2
  
  std::cout<<"map size="<<m1.size()<<std::endl;    //step -3  
}
