#include <iostream>
#include <random>
#include <ctime>

constexpr std::size_t NPICS = 3 ;

void display( unsigned int c )
{
    static const char* const pictures[NPICS] =
    {
        "          .:'      \n"
        "      __ :'__      \n"
        "   .'`  `-'  ``.   \n"
        "  :            :   \n"
        "  :            :   \n"
        "  :           :    \n"
        "   `.__.-.__.'     \n",

        "       )          \n"
        "      C,          \n"
        "     ( ~)         \n"
        "     ( ~)         \n"
        "     (~ )         \n"
        "     \\~~/         \n"
        "      \\/          \n",

        "  __________    '.  :  .'  \n"
        " /         /\\__.__'.:.'  . \n"
        " \\_________\\/  .  .':'.  . \n"
        "                .'  :  '.  \n"
     };


     std::cout << pictures[ c % NPICS ] ;
}

void spinner()
{
    // http://en.cppreference.com/w/cpp/numeric/random
    static std::mt19937 rng( std::time(nullptr) ) ;
    static std::uniform_int_distribution<int> random_colour( 0, 1 ) ;
    static const char* const colours[] = { "RED", "GREEN" } ;
    std::cout << "set colour " << colours[ random_colour(rng) ]  << '\n' ;

    static std::uniform_int_distribution<int> random_picture( 0, NPICS ) ;
    display( random_picture(rng) ) ;
    std::cout << "------------------------------\n" ;
}

int main()
{
    for( int i = 0 ; i < 8 ; ++i ) spinner() ;
}
