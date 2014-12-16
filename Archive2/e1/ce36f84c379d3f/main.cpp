/*To compile using clang or gcc, simply use
    'compiler_name' -std=c++11 -o 'binary_name' 'file_name' \
    e.g on Linux, you may have

    clang++ -std=c++11 -o merge_sort merge_sort.cpp && ./merge_sort
*/

#include <iostream>
#include <algorithm>
#include <forward_list>

namespace MergeSortAlgorithm
{
    //~ used to determine type traits.
    template<typename T>
    struct type
    {
        using tag =             typename std::iterator_traits<T>::iterator_category;
        using value_type =      typename std::iterator_traits<T>::value_type;
    };

    inline namespace implementation_details
    {
        template< typename Iter >
        inline void merge_splitted_containers( Iter beg, Iter mid, Iter end )
        {
            std::inplace_merge( beg, mid, end );
        }
        
        template< typename Iter >
        void merge_sort_impl( Iter first, Iter end, std::random_access_iterator_tag tag )
        {
            auto size = std::distance( first, end );
            if( size <= 1 ) return;
    
            Iter middle = first + ( size / 2 );
    
            merge_sort_impl( first, middle, tag );
            merge_sort_impl( middle, end, tag );
    
            implementation_details::merge_splitted_containers( first, middle, end );
        }
            
        template< typename Iter >
        void merge_sort_impl( Iter beg, Iter end, std::forward_iterator_tag )
        {
            using data_type = typename type< Iter >::value_type;
            std::vector< data_type > vector { beg, end };
            using tag_type = typename type< typename std::vector< data_type >::iterator >::tag;
            merge_sort_impl( vector.begin(), vector.end(), tag_type{} );

            //~ Iter temp = beg;
            for( auto new_beg = vector.begin(), new_end = vector.end(); new_beg != new_end; ++new_beg )
            {
                *beg++ = std::move( *new_beg );
            }
        }
    } //~ namespace implementation_details
    
    //~ sort based on two iterators e.g. std::begin( std::vector ) and std::end( std::vector )
    template< typename Iter >
    inline void merge_sort( Iter first, Iter second )
    {
        using tag_type = typename type< Iter >::tag;
        merge_sort_impl( first, second, tag_type() );
    }
    
    //~ standard containers including std::vector, std::list, std::forward_list
    template< typename T >
    inline void merge_sort( T & container )
    {
        using tag_type = typename type<typename T::iterator>::tag; //get the iterator category.
        merge_sort_impl( std::begin( container ), std::end( container ), tag_type() ); //make call based on iterator category
    }

    //~ Normal built-in array
    template<typename T, size_t N>
    inline void merge_sort( T ( & container ) [N] )
    {
        using tag_type = typename type < decltype( std::begin( container ) )>::tag;
        merge_sort_impl( container, container + N, tag_type() );
    }
    
} //namespace MergeSortAlgo

//pseudo random number generator
inline int rng()
{
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    return dis( rd );
}

using namespace MergeSortAlgorithm;

auto main() -> int
{
    
    int a [] = { 11, 2, 30, 24, 644, 34, 324, 57 };
    std::string names[] { "Josh", "Ogunyinka", "C++", "Concepts", "Charles", "Okubo", "Ibori", "James" };
    auto reg = std::vector< double > ( 40 );
    std::generate( reg.begin(), reg.end(), rng ); //~ let the program generate random numbers through rng
    
    std::forward_list< double > reg_list = { 12.3, 45.5, 6.4, 34.6, 2.4, 43.4 };
    

    size_t size = sizeof( a ) / sizeof( int );
    std::cout << "Sorting built-in array of type 'int'..." << std::endl;
    merge_sort( std::begin( a ), std::end( a ) );

    for( unsigned int i = 0; i != size; ++i )
        std::cout << a[ i ] << ", ";
    std::cout << "\n\n";

    std::cout << "Sorting built-in array of type 'std::string'..." << std::endl;
    merge_sort( names );
    for( auto beg = std::begin( names ), end = std::end( names ); beg != end; ++beg )
        std::cout << *beg << ", ";
    std::cout << "\n\n";

    std::cout << "Sorting std::vector< double >..." << std::endl;
    merge_sort( reg.begin(), reg.end() );
    std::for_each( reg.cbegin(), reg.cend(), []( double const & r )-> void { std::cout << r << ", "; } );
    std::cout << "\n\n";

    std::cout << "Sorting std::forward_list< double >..." << std::endl;
    merge_sort( reg_list );
    for( const auto &i: reg_list ) std::cout << i << ", ";
    return EXIT_SUCCESS;
}
