#include <iostream>
#include <fstream>
#include <vector>

void PrintVec( std::vector< std::vector<double> > const & v, std::ostream& stm )
{
   for( std::size_t i = 0; i < v.size() ; ++i )
   {
       for( std::size_t j = 0 ; j < v[i].size() ; ++j ) stm << v[i][j] << ' ' ;
	   stm << "  |   " ;
   }
   stm << '\n' ;
}

void PrintVec( std::vector<double> const & v, std::ostream& stm )
{
   for( std::size_t i = 0; i < v.size() ; ++i ) stm << v[i] << ' ' ;
   stm << '\n' ;
}

int main()
{
    std::ofstream file( "myexample.txt" ) ;

    std::vector<double> one_d{ 0, 1, 2, 3, 4 } ;
    PrintVec( one_d, file ) ;

    std::vector< std::vector<double> > two_d{ { 0, 1, 2 },  { 3, 4 }, { 5 }, { 6, 7, 8, 9 } } ;
    PrintVec( two_d, file ) ;
}
