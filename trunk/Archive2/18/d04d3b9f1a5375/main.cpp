#include <list>
#include <map>
#include <typeindex>
#include <type_traits>
#include <iostream>
#include <iomanip>

struct UndeadMonster { virtual ~UndeadMonster() = default ; /* ... */ };
struct Skeleton : UndeadMonster { /* ... */ } ;
struct Zombie : UndeadMonster { /* ... */ } ;
struct Ghoul : UndeadMonster { /* ... */ } ;

std::map< std::type_index, std::list<UndeadMonster*> > lists ;

void foo( UndeadMonster* monster )
{ lists[ std::type_index( typeid(*monster) ) ].push_back(monster) ; }

int main()
{
    UndeadMonster* monsters[] = { new Zombie, new Skeleton, new Ghoul, new Skeleton, new Zombie, new Ghoul, new Zombie, new Ghoul } ;
    for( auto ptr : monsters ) foo(ptr) ;
    
    // iteratoe through the lists
    std::cout << "lists\n--------------\n" ;
    for( const auto& pair : lists )
    {
        std::cout << std::setw(12) << pair.first.name() << "  -  " ;
        for( auto p : pair.second ) std::cout << p << "  " ;
        std::cout << '\n' ;
    }
}
