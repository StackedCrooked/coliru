#include <iostream>
#include <list>
#include <map>

struct patient { int nas ; /* ... */ };

int main()
{
    patient a[] = { { 420 /*,...*/ }, { 250 /*,...*/ }, { 420 /*,...*/ }, { 666 /*,...*/ },
                    { 444 /*,...*/ }, { 777 /*,...*/ }, { 250 /*,...*/ }, { 666 /*,...*/ },
                    { 100 /*,...*/ }, { 666 /*,...*/ }, { 250 /*,...*/ }, { 666 /*,...*/ }}  ;
    std::list< patient* > ListePatient ;
    for( patient& p : a ) ListePatient.push_back( &p ) ;

    std::map<int,int> frequency_counter ;
    for( const auto ptr : ListePatient ) if(ptr) ++frequency_counter[ptr->nas] ;

    for( auto pair : frequency_counter )
        std::cout << pair.first << " appears " << pair.second << " time(s).\n" ;
    std::cout << "#unique values: " << frequency_counter.size() << '\n' ;
}
