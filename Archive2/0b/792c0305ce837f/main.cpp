#include <iostream>
#include <string>
#include <vector>
#include <map>

int main()
{
    {
        std::map< std::string, std::vector<int> > map ;

        const std::pair< std::string, int > kv_pairs[] =
        {
            std::make_pair( "one", 1 ), std::make_pair( "two", 2 ),
            std::make_pair( "three", 3 ), std::make_pair( "one", 4 ),
            std::make_pair( "two", 5 ), std::make_pair( "one", 6 ),
            std::make_pair( "three", 7 ), std::make_pair( "one", 8 ),
            std::make_pair( "two", 9 ), std::make_pair( "one", 10 )
        };

        const int N = sizeof(kv_pairs) / sizeof( kv_pairs[0] ) ;

        for( int i = 0 ; i < N ; ++i )
        {
            const std::string& key = kv_pairs[i].first ;
            const int value = kv_pairs[i].second ;
            map[key].push_back(value) ;
        }

        std::map< std::string, std::vector<int> >::iterator iter = map.begin() ;
        for(  ; iter != map.end() ; ++iter )
        {
            const std::string& key = iter->first ;
            std::cout << "key: '" << key << "'  values: " ;

            const std::vector<int>& values = iter->second ;
            for( std::size_t i = 0 ; i < values.size() ; ++i )
                std::cout << values[i] << ' ' ;
            std::cout << '\n' ;
        }
    }
}
