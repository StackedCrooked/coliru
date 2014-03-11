#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

struct st
{
    int rank;
	std::string name;
	double hight;

	bool operator< ( st that ) const { return rank < that.rank ; }
	bool operator== ( st that ) const { return rank == that.rank ; }
    // ...
};

int main()
{
    std::vector<st> seq = { { 20, "kimi", 1 }, { 7, "papu", 2 }, { 10, "avi", 3 },
            { 8, "pavi", 4 }, { 7, "hen", 5 }, { 15, "cucu", 6 }, { 20, "miki", 7 } } ;

	std::sort( seq.begin(), seq.end() ) ;
    
    // http://en.cppreference.com/w/cpp/algorithm/adjacent_find
	for( auto iter = std::adjacent_find( seq.begin(), seq.end() ) ;
	      iter != seq.end() ;
	      iter = std::adjacent_find( iter, seq.end() ) )
    {
        for( int rank = iter->rank ; iter != seq.end() && rank == iter->rank ; ++iter )
             std::cout << "RANK: " << rank << " ---- " << iter->name << '\n' ;
        std::cout << '\n' ;     
    }
}
