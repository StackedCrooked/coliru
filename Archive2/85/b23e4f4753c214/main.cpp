#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <vector>

using namespace boost;

struct worker1
{
   void init()
   {
      std::cout << "Worker1 init called" << std::endl;
   }
};

struct worker2
{
   void init()
   {
      std::cout << "Worker2 init called" << std::endl;
   }
};

typedef mpl::vector< worker1, worker2> workers;

template< typename U> struct process3
{
   process3()
   {
      factory();
   }

   struct factoryrun
   {
      template< typename T > void operator()(T& x)
      {
         std::cout << "Factory entry" << std::endl;
         std::cout << "Type is = " << typeid( T ).name() << std::endl;

         m_t.push_back( x ); // MISPRINT!
      }
   };

   struct runinit
   {
      template<typename T> void operator()(T& x)
      {
         x.init();
      }
   };

   void init()
   {
      mpl::for_each<U>( runinit() );
   }

   void factory()
   {
      std::cout << "Factory start" << std::endl;
      mpl::for_each<U>( factoryrun() );
   }

   typedef typename boost::make_variant_over< U >::type types;
   typedef std::vector< boost::variant<types> > Vector; // Make typedef to simplify
   static Vector m_t;
};

template<typename U> typename process3<U>::Vector process3<U>::m_t; // MISPRINT!!!

int main() {
   process3<workers> prs;
   // Here should be called init() for worker1 and worker2
   prs.init();
   return 0;
}
