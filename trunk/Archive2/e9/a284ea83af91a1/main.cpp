#include <iostream>
#include <typeinfo>
#include <boost/variant.hpp>
#include <exception>
template<typename T>
using EnableIf = typename std::enable_if <  std::is_same<T, int>::value    ||
                                            std::is_same<T, float>::value  ||
                                            std::is_same<T, std::string>::value
                                         >::type* ;

typedef boost::variant< int, float, std::string > var ;


struct sig
{
    sig( ):s(),vis ( std::cout ) 
    { 
    }
    
    template <typename T, EnableIf<T> = nullptr >
    sig(const T& s, std::ostream& logger =std::cout ):s(s), vis ( logger )
    {   
        
    }
    /*
    template <typename T, EnableIf<T> = nullptr >
    sig(const T& s):s(s), vis ( std::cout  )
    {   
        
    }
    */
    
    template <typename T, EnableIf<T> = nullptr >
    sig& operator=(const T& s) 
    {
        this->s = s;
        return *this ;
    }
    
    sig(const sig& s):s( s.s ), vis ( s.vis )
    {   
        
    }

    
    template<typename T>
    operator T() const 
    {
        try 
        {
            std::cout << "Here : " ;
            T temp { *boost::get<T>(&s) };
            
            return temp ;
        } 
        catch (const boost::bad_get&) 
        {
            throw std::runtime_error("Bad Casting");
        }
    }

    struct visit : boost::static_visitor<>
    {
        template<typename T, EnableIf<T> = nullptr >
        void operator()( const T& t ) const
        {
            _os << t ;
            
        }
        visit( std::ostream& os ):_os(os)
        {
        }
        private:
            std::ostream &_os ;
    };
    
    
    friend std::ostream& operator<< ( std::ostream& os, const sig& s ) ;
    private:
        var s;
        visit vis ;
};
    
std::ostream& operator<< ( std::ostream& os, const sig& s ) 
{
    boost::apply_visitor( s.vis, s.s );
    return os ;
}

int main()
{
  sig s1 = 6.3f  ;
  sig s2  ;
  s2 = std::string("Jack") ; ;
  std::cout << s2 << s1 ;
  
  //int s = s2 ;
}