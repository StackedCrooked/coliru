#include <iostream>

struct A
{
    int  a;

    #if 0
    bool operator==( const A& rhs ) const
    {
        return ( a==rhs.a);
    }
    #endif
};
#if 1
bool operator==( const A &l,const A &r )
{
    return ( l.a==r.a);
}
#endif

namespace CHECK
{
  typedef char no[7];
  template<typename T> no& operator == (const T&, const T&);
      
   template < typename T >
   struct opEqualExists
   {
     enum { value = (sizeof(*new T[1] == *new T[1]) != sizeof(no)) };
   };
}
int main()
{
    std::cout<<CHECK::opEqualExists<A>::value<<std::endl;
}