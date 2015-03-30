#include <iostream>
#include <string>

static int depth = 0 ;

// return the index if the value is found; -1 if value isn't found
int find( const int array[], int array_size, int pos, int value_to_find ) // const
{
    if( pos == 0 ) depth = 0 ;
    else ++depth ;
    
    std::string tab( depth*2, ' ' ) ;
    tab += std::to_string(depth) + ". " ;

    std::cout << tab << "array_size: " << array_size << " pos: " << pos << " value_to_find: " << value_to_find << " => " ;
    // if we have reached the end of the array and not found the value
    if( pos >= array_size )
    {
        std::cout << value_to_find << " not found in positons 0 to " << array_size-1 << " - return -1\n" ;
        --depth ;
        return -1 ;
    }

    // if the value we are looking for is at index pos
    else if( array[pos] == value_to_find )
    {
        std::cout << value_to_find << " found at position " << pos << " - return " << pos << '\n' ;
        --depth ;
        return pos ;
    }

    // recursively call find for positions on the right, starting at pos+1
    else
    {
        std::cout << value_to_find << " not found at position " << pos << " - return find( ... " << pos+1 << " ... )\n" ;
        const int f = find( array, array_size, pos+1, value_to_find ) ;
        std::cout << tab << " find returned " << f << " - return " << f << '\n' ;
        --depth ;
        return f ;
    }
}

int main()
{
    const int N = 5 ;
    const int a[N] = { 0, 1, 2, 3, 4 };

    int f = find( a, N, 0, 0 ) ; std::cout << "\n *** result is " << f << " ***\n------------------\n" ; // 0
    f = find( a, N, 0, 2 ) ;  std::cout << "\n *** result is " << f << " ***\n------------------\n" ;// 2
    f = find( a, N, 0, 4 ) ; std::cout << "\n *** result is " << f << " ***\n------------------\n" ;// 4
    f = find( a, N, 0, 6 ) ; std::cout << "\n *** result is " << f << " ***\n------------------\n" ; // -1
}
