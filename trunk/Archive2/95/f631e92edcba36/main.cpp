#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>

std::set< std::tuple<int,int,int> > unique_zero_3sum_tuples( std::vector<int> seq )
{
    std::set< std::tuple<int,int,int> > tuples ;

    const int n = seq.size() ;
    if( n > 2 )
    {
    	sort( seq.begin(), seq.end() ) ;
		const int end = n - 2 ;

		for( int first = 0 ; first < end && seq[first] < 1 ; ++first )
        {

			int second = first + 1 ;
			int third = end + 1 ;

			while( second < third )
            {
				int sum = seq[first] + seq[second] + seq[third] ;

				if( sum == 0)
                {
                    tuples.insert( std::make_tuple( seq[first], seq[second], seq[third] ) ) ;
                    ++second ;
                    --third ;
				}

				else if( sum > 0 ) --third ;

				else ++second ; // sum < 0
			}
		}
    }
    
    return tuples ;
}

void print_unique_zero_3sum_triplets( std::vector<int> seq )
{
    for( const auto& tup : unique_zero_3sum_tuples(seq) )
        std::cout << std::get<0>(tup) << ' ' << std::get<1>(tup) << ' ' << std::get<2>(tup) << '\n' ;
}

int main()
{
    print_unique_zero_3sum_triplets( { -10, -10, -20, -20, 30, 30, -5, 25, 15, 15, -2, 12, 12 } ) ;
    std::cout << "------------------------\n" ;
    print_unique_zero_3sum_triplets( { -25, -10, -7, -3, 1, 2, 3, 4, 5, 8, 10, 13, 15, 17, 28, -10, -7, -3, 1, 2 } ) ;
}
