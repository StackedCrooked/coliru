#include <iostream>
#include <cstdlib>
#include <ctime>

class die {

    public:
        static const int NUM_FACES = 6  ;

        int roll()
        {
            const int n = std::rand() % NUM_FACES + 1 ;
            ++faceRolled[n] ;
            return n ;
        }

        int count( int face ) const
        { return face > 0 && face <= NUM_FACES ?  faceRolled[face] : 0 ; }

    private:
        int faceRolled[NUM_FACES+1] = {0}; // initialise with all zeroes
};

int main()
{
    const int N = die::NUM_FACES * 32000000 ;
    std::srand( std::time(0) ) ;

    die a_die ;
    for( int i = 0 ; i < N ; ++i ) a_die.roll() ;
    for( int face = 1 ; face <= die::NUM_FACES ; ++face )
        std::cout  << face << ". " << a_die.count(face) << '\n' ;
}
