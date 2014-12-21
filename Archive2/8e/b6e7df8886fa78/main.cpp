#include <iostream>
#include <queue>

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

        bool operator() ( int a, int b ) const
        { return sum_digits(a) < sum_digits(b) ; }
    };

    std::priority_queue< int, std::vector<int>, cmp_sum_of_digits > pq ;
    for( int v : { 1234, 99, 56, 86, 7, 70, 700, 234, 34, 11211, 114 } ) pq.push(v) ;

    while( !pq.empty() ) { std::cout << pq.top() << ' ' ; pq.pop() ; }
    std::cout << '\n' ;
}
