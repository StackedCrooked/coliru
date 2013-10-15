#include <iostream>
#include <utility>
#include <type_traits>

// an enum we would like to support
enum class tribool { FALSE, TRUE, FILE_NOT_FOUND };

// declare basic generic template
// (independent of a specific function you'd like to call)
template< template< class > class CB, std::size_t N, typename = std::tuple<> >
struct var_to_template;

// register types that should be supported
template< template< class > class CB, std::size_t N, typename... Cs >
struct var_to_template< CB, N, std::tuple< Cs... > >
{
   // bool is pretty simple, there are only two values
   template< typename R, typename... Args >
   static R impl( bool b, Args&&... args )
   {
      return b
        ? var_to_template< CB, N-1, std::tuple< Cs..., std::true_type > >::template impl< R >( std::forward< Args >( args )... )
        : var_to_template< CB, N-1, std::tuple< Cs..., std::false_type > >::template impl< R >( std::forward< Args >( args )... );
   }

   // for each enum, you need to register all its values
   template< typename R, typename... Args >
   static R impl( tribool tb, Args&&... args )
   {
      switch( tb ) {
        case tribool::FALSE:
          return var_to_template< CB, N-1, std::tuple< Cs..., std::integral_constant< tribool, tribool::FALSE > > >::template impl< R >( std::forward< Args >( args )... );
        case tribool::TRUE:
          return var_to_template< CB, N-1, std::tuple< Cs..., std::integral_constant< tribool, tribool::TRUE > > >::template impl< R >( std::forward< Args >( args )... );
        case tribool::FILE_NOT_FOUND:
          return var_to_template< CB, N-1, std::tuple< Cs..., std::integral_constant< tribool, tribool::FILE_NOT_FOUND > > >::template impl< R >( std::forward< Args >( args )... );
      }
      throw "unreachable";
   }
   
   // in theory you could also add int, long, ... but
   // you'd have to switch on every possible value that you want to support!
};

// terminate the recursion
template< template< class > class CB, typename... Cs >
struct var_to_template< CB, 0, std::tuple< Cs... > >
{
   template< typename R, typename... Args >
   static R impl( Args&&... args )
   {
      return CB< std::tuple< Cs... > >::template impl< R >( std::forward< Args >( args )... );
   }
};

// here's your function with the template parameters
template< bool B, tribool TB >
int HeavyLoop_impl( int arg )
{
   for (int i = 0; i < 10000000; i++) {
      arg += B ? 1 : 2;
      arg += ( TB == tribool::TRUE ) ? 10 : ( TB == tribool::FALSE ) ? 20 : 30;
   }
   return arg;
}

// a helper class, required once per function that you'd like to forward
template< typename > struct HeavyLoop_callback;
template< typename... Cs >
struct HeavyLoop_callback< std::tuple< Cs... > >
{
   template< typename R, typename... Args >
   static R impl( Args&&... args )
   {
      return HeavyLoop_impl< Cs::value... >( std::forward< Args >( args )... );
   }
};

// and here, everything comes together:
int HeavyLoop( bool b, tribool tb, int arg )
{
   // you provide the helper and the number of arguments
   // that should be converted to var_to_template<>
   // and you provide the return type to impl<>
   return var_to_template< HeavyLoop_callback, 2 >::impl< int >( b, tb, arg );
}

int main()
{
   bool b = true;
   tribool tb = tribool::FALSE;
   int arg = 0;
   int res = HeavyLoop( b, tb, arg );
   std::cout << "res: " << res << std::endl;
   return 0;
}
