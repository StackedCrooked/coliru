#include <iostream>
#include <functional>
#include <string>

template < typename RESULT_TYPE, typename... ARG_TYPES > struct A
{
    std::function< RESULT_TYPE( ARG_TYPES&&... ) > fn ;

    RESULT_TYPE operator() ( ARG_TYPES&&... args ) const { return fn( std::forward<ARG_TYPES>(args)... ) ; }
};

int main()
{
    A< std::string::size_type, const std::string& > strlen { &std::string::size } ;
    A< std::ostream&, std::ostream&, int, char > setwf =
        { [] ( std::ostream& stm, int w, char f ) -> std::ostream& { stm.width(w) ; stm.fill(f) ; return stm ; } } ;

    const std::string str = "hello world!" ;
    setwf( std::cout, 5, '*' ) << strlen(str) << '\n' ;
}
