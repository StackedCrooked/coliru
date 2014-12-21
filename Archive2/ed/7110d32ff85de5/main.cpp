#include <iostream>
#include <queue>
#include <utility>

int main()
{
    struct cmp_sum_of_digits
    {
        static int sum_digits( int n )
        {
            if( n < 0 ) n = -n ;
            int s = 0 ;
            while(n) { s += n%10 ; n /= 10 ; }
            return s ;
        }

        static int sum_digits( std::pair<int,int> p )
        { return sum_digits( p.first ) + sum_digits( p.second ) ; }

        bool operator() ( std::pair<int,int> a, std::pair<int,int> b ) const
        { return sum_digits(a) < sum_digits(b) ; }
    };

    using pair =  std::pair<int,int> ;
    std::priority_queue< pair, std::vector<pair>, cmp_sum_of_digits > pq ;
    const std::initializer_list<pair> ilist = { {123,4}, {9,9}, {5,6}, {8,6}, {0,7}, {70,0}, {700,0}, {23,4}, {112,111}, {114,9} } ;
    for( pair v : ilist ) pq.push(v) ;

    while( !pq.empty() )
    {
        std::cout << '{' << pq.top().first << ',' << pq.top().second << "} " ;
        pq.pop() ;
    }
    std::cout << '\n' ;
}
