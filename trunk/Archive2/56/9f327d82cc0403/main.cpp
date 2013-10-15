#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <iomanip>

struct student
{
    int id;
    int score;
};

// generate 'n' random unique ids in [1,n],
// random non-unique scores in [0,100]
void generate( student* students, std::size_t n )
{
    // generate ids in sequence 1, 2, 3, 4, ... n
    // generate random scores in [0,100]
    for( std::size_t i = 0 ; i < n ; ++i )
    {
        students[i].id = i+1 ;
        students[i].score = std::rand() % 101 ;
    }

    // form a random permutation of the students
    // http://www.cplusplus.com/reference/algorithm/random_shuffle/
    std::random_shuffle( students, students+n ) ;
}

int main()
{
    std::srand( std::time(nullptr) ) ; // seed just once, at the beginning of main

    constexpr std::size_t N = 15 ;
    student students[N] ;

    generate( students, N ) ;

    for( const student& s : students )
        std::cout << std::setw(2) << s.id << ". " << std::setw(3) << s.score << '\n' ;
}
