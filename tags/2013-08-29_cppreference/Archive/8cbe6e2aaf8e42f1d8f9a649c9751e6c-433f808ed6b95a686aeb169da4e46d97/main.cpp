#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <iostream>

static int _sort( const void* a, const void *b )
{return strcmp ( * ( const char * * ) a , * ( const char * * ) b ) ; }

void do_qsort ( std :: vector < const char * > in) {
    unsigned long long ts = __rdtsc ( ) ;
    qsort ( & in [ 0 ] , in . size () , sizeof ( const char * ) , _sort ) ;
    std :: cout << "qsort     " << ( __rdtsc ( ) - ts )  << '\n' ;
}

void do_stdsort ( std :: vector < const char * > in ) {
    unsigned long long ts = __rdtsc ( ) ;
    std :: sort ( in . begin ( ) , in . end ( ) , [ ] ( const char * a , const char * b ) { return strcmp ( a , b ) < 0 ; } ) ;
    std :: cout << "std::sort " << ( __rdtsc ( ) - ts )  << '\n' ;
}

int main ( ) 
{
    std :: istream_iterator < std :: string > in ( std :: cin ) , out ;
    std :: vector < std :: string > holder ;
    std :: copy ( in, out, std :: back_inserter ( holder ) ) ;
    
    std :: vector< char const * > ptrs ( holder . size ( ) ) ;
    std :: transform ( holder . begin ( ) , holder . end ( ) , ptrs . begin ( ) , std :: mem_fn ( & std :: string :: c_str ) ) ;
    
    std:: cout << "sorting " << ptrs . size() << " words.\n" ;                   
    do_qsort( ptrs ) ;
    do_qsort( ptrs ) ;
    do_qsort( ptrs ) ;
    do_qsort( ptrs ) ;
    do_qsort( ptrs ) ;
    do_stdsort( ptrs ) ;
    do_stdsort( ptrs ) ;
    do_stdsort( ptrs ) ;
    do_stdsort( ptrs ) ;
    do_stdsort( ptrs ) ;
    
    std :: copy( holder . begin ( ) , holder . end ( ) , std :: ostream_iterator< std :: string > ( std :: cout , " " ) ) ;
    
    return 0 ;
}