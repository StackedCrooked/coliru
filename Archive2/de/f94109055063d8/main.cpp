#include <iostream>

enum epoch { Neogene = 23, Paleogene = 65, Cretaceous = 136, Jurassic = 192, Triassic = 225, Permian = 280,
             Carboniferous = 345, Devonian = 395, Silurian = 435, Ordovician = 500, Cambrian = 570, Precambrian = 4500 } ;

const int epoch_end[] = { Neogene, Paleogene, Cretaceous, Jurassic, Triassic, Permian,
                          Carboniferous, Devonian, Silurian, Ordovician, Cambrian, Precambrian } ;

const int N = sizeof(epoch_end) / sizeof( epoch_end[0] ) ;

const char* const epoch_name[N] = { "Neogene", "Paleogene", "Cretaceous", "Jurassic", "Triassic", "Permian",
	                                "Carboniferous", "Devonian", "Silurian", "Ordovician", "Cambrian", "Precambrian" } ;

int main ()
{
	int start_year, end_year ; // these go backwards
	std::cin >> start_year >> end_year ;

	int i = 0 ;
	while( start_year > epoch_end[i] ) ++i ; // get to the epoch of the start year

	while( end_year > epoch_end[i] && i < N ) // keep going back through epochs till we reach end_year
    {
        std::cout << epoch_name[i] << ' ' ; // print the name of each epoch as we pass through it
        ++i ;
    }
    if( i < N ) std::cout << epoch_name[i] << '\n' ; // print the epoch of the end_year
	else std::cout << "before Precambrian\n" ;
}
