#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main()
{
    {
        std::unordered_map< std::string, std::vector<int> > hash_map ;

        std::pair< std::string, int > kv_pairs[] =
        {
            { "one", 1 }, { "two", 2 }, { "three", 3 }, { "one", 4 }, { "two", 5 },
            { "one", 6 }, { "three", 7 }, { "one", 8 }, { "two", 9 }, { "one", 10 }
        };

        for( const auto& p : kv_pairs ) hash_map[p.first].push_back(p.second) ;

        for( const auto& kv : hash_map )
        {
            std::cout << "key: '" << kv.first << "'  values: " ;
            for( int v : kv.second ) std::cout << v << ' ' ;
            std::cout << '\n' ;
        }
    }
}
