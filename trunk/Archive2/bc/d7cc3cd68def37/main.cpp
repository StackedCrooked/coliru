#include <map>
#include <iostream>

struct mapWrapper
{
    size_t& operator [] (int n )
    {
        std::cout << "operator []\n" ;
        return m_[n] ;
    }
    
    size_t size() const
    {
        std::cout << "size()\n" ;
        return m_.size() ;
    }
    
    std::map <int, size_t> m_ ;
};

int main() {
  std::map<int, size_t> m;
  m[0] = m.size();

   std::cout << m[0] << std::endl ;
   
   mapWrapper mw ;
   
   mw[0] = mw.size() ;
   
   std::cout << mw[0] << std::endl ;
}