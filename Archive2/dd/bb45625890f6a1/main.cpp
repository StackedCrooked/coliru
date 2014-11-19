//Title of this code

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/variant.hpp>

typedef boost::variant< int, float, std::string > var ;


struct visit: public boost::static_visitor<>
{
    visit(  ): size(0) { }
    template<typename T>
    void operator()(  T& x) const
    {
        
        size += sizeof ( x ) ;
       // std::cout <<  sizeof ( x ) << ":" << x << '\n';
    }
    
    std::size_t get_size() const
    { return size ; }
    private:
        mutable std::size_t size ;
        
 
};



int main()
{
    std::vector< var > vec;
    
    vec.push_back(1.2f);
    vec.push_back("jack");
    vec.push_back(123);
   
    
    visit visito ;
    std::for_each( vec.begin(), vec.end(), 
                   boost::apply_visitor( visito) );
              
    std::cout << visito.get_size() ;
   
}