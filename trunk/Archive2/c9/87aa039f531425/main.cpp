#include <iostream>
#include <map>
#include <vector>

struct thing { std::string data ; };

int main()
{
    std::vector<thing> things { {"zero"}, {"one"}, {"two"}, {"three"}, {"zero"}, {"two"} } ;
    const thing* p = std::addressof( things.front() ) ;

    struct container { std::string name ; std::vector<const thing*> objects ; } ;
    container containers[] =
    {
        { "first container", { p+4, p, p+3, p+4, p+1, p+5, p+2, p+4, p, p+2, p+3 } },
        { "second container", { p+3, p+2, p, p+5, p+2, p+4, p+3, p+1 } }
    };

    std::size_t seq_number = 0 ;
    std::map< const thing*, std::size_t > object_map ;

    // populate object map
    for( const auto& cntr : containers )
    {
        for( const thing* ptr : cntr.objects )
        {
            auto iter = object_map.find(ptr) ;
            if( iter == object_map.end() ) object_map.emplace( ptr, seq_number++ ) ;
        }
    }

    // write object map
    std::cout << "objects are: \n" ;
    for( const auto& pair : object_map )
        std::cout << '#' << pair.second << ' ' << pair.first->data << '\n' ;

    // write object sequence numbers in container
    for( const auto& cntr : containers )
    {
        std::cout << '\n' << cntr.name << " holds objects: " ;
        for( const thing* ptr : cntr.objects ) std::cout << '#' << object_map[ptr] << ' ' ;
        std::cout << '\n' ;
    }

    // input would be symmetric:
    // 1. read and create object map
    // 2. read sequence numbers and populate containers from map
}
