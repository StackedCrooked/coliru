#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::string pigeUnMot( std::string chemin )
{
    std::ifstream flux( chemin ) ;
    std::string motChoisit ;

    int nbMots = 0 ;
    std::string line ;
    while( std::getline( flux, line ) )
    {
        if( !line.empty() )
        {
            ++nbMots ;
            if( std::rand() % nbMots == 0 ) std::swap( motChoisit, line ) ;
        }
    }

    return motChoisit ;
}

std::string melangeLettres( std::string mot )
{
    std::random_shuffle( mot.begin(), mot.end() ) ;
    return mot ;
}

int main()
{
    const std::string test_file = "test.txt" ;

    // create a test file
    {
        std::ofstream(test_file) << "electrocardiographically\n"
                                    "indistinguishability\n"
                                    "phosphorescence\n"
                                    "countersurveillance\n"
                                    "sleeplessness\n"
                                    "antediluvian\n" ;
    }

    std::srand( std::time(nullptr) ) ;

    for( int i = 0 ; i < 5 ; ++i )
    {
        const std::string motMystere = pigeUnMot( test_file ) ;
        const std::string motMelange = melangeLettres(motMystere) ;

        std::cout << "Quel mot mystère se cache derrière: " << motMelange << "?\n\n" ;
    }
}
