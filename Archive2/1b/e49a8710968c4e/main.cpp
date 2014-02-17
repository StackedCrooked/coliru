#include <list>
#include <map>
#include <typeindex>
#include <type_traits>
#include <iostream>

struct UndeadMonster { virtual ~UndeadMonster() = default ; /* ... */ };
struct Skeleton : UndeadMonster { /* ... */ } ;
struct Zombie : UndeadMonster { /* ... */ } ;
struct Ghoul : UndeadMonster { /* ... */ } ;

std::map< std::type_index, std::list<UndeadMonster*> > lists ;

void foo( UndeadMonster* monster )
{ lists[ std::type_index( typeid(*monster) ) ].push_back(monster) ; }

int main()
{
    Zombie z ;
    foo( &z ) ;
    std::cout << lists[ std::type_index( typeid(Zombie) ) ].size() << ' ' 
              << lists[ std::type_index( typeid(Zombie) ) ].front() << ' ' 
              << std::addressof(z) << '\n' ;
}
