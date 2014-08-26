#include <iostream>
#include <tuple>
#include <vector>

namespace detail
{
    template < typename TUPLE, std::size_t CURR, std::size_t SIZE >
    struct printer
    {
        static std::ostream& print( std::ostream& stm, const TUPLE& tup )
        {
            stm << ", " << std::get<CURR>(tup) ;
            return printer< TUPLE, CURR+1, SIZE >::print( stm, tup ) ;
        }
    };

    template < typename TUPLE, std::size_t SIZE > struct printer<TUPLE,0,SIZE>
    {
        static std::ostream& print( std::ostream& stm, const TUPLE& tup )
        {
            stm << "{ " << std::get<0>(tup) ;
            return printer< TUPLE, 1, SIZE >::print( stm, tup ) ;
        }
    };

    template < typename TUPLE, std::size_t SIZE > struct printer<TUPLE,SIZE,SIZE>
    { static std::ostream& print( std::ostream& stm, const TUPLE& ) { return stm << " }" ; } };

    template < typename TUPLE > struct printer< TUPLE, 0, 0 >
    { static std::ostream& print( std::ostream& stm, const TUPLE& ) { return stm << "{}" ; } };
}

template < typename... TYPES >
std::ostream& operator<< ( std::ostream& stm, const std::tuple<TYPES...>& tup )
{ return detail::printer< std::tuple<TYPES...>, 0, sizeof...(TYPES) >::print( stm, tup ) ; }

enum weekday { monday, tuesday, wednesday, thursday, friday, saturday, sunday } ;

std::ostream& operator<< ( std::ostream& stm, weekday wd )
{
    static const char* const txt[] { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Satudrday", "Sunday" } ;
    return stm << ( wd >= monday && wd <= sunday ? txt[wd] : "??????" ) ;
}

int main()
{
    using tuple_type = std::tuple< weekday, int, std::string > ;
    const std::vector<tuple_type> todo_list = {
        tuple_type{ monday,  900, "purchase meat" },
        tuple_type{ tuesday, 1400, "beat meat" },
        tuple_type{ wednesday, 1100, "make sandwiches" },
        tuple_type{ thursday, 1200, "eat sandwiches" },
        tuple_type{ friday, 1200, "reinvent wheel" },
        tuple_type{ saturday,  800, "post cats" },
        tuple_type{ sunday, 2200, "post sinks (mods asleep)" }
    };
    for( auto& tup : todo_list ) std::cout << tup << '\n' ;
}
