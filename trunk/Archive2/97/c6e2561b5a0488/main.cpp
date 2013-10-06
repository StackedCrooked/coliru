#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

template< typename VERTEX_TYPE >
    using adjacency_list_type = std::map< VERTEX_TYPE, std::vector<VERTEX_TYPE> > ;

using adjacency_list = adjacency_list_type<int> ;

// input is a pair for each edge in a DAG (vertex_from, vertex_to)
// 1 7 => edge from 1 -------> 7
// 2 7 => edge from 2 -------> 7
// 1 5 => edge from 1 -------> 5
// etc.
adjacency_list create( std::istream& stm )
{
    adjacency_list graph ;
    int a, b ;
    while( stm >> a >> b ) { graph[a].push_back(b) ; graph[b] ; }
    return graph ;
}

bool topological_sort( const adjacency_list& graph )
{
    std::map<int,int> num_pred_map ;
    for( auto& pair : graph )
    {
         num_pred_map[pair.first] ;
         for( auto n : pair.second ) ++num_pred_map[n] ;
    }

    while( !num_pred_map.empty() )
    {
        bool cyclic = true ;
        for( auto iter = num_pred_map.begin() ; iter != num_pred_map.end() ; )
        {
            if( iter->second == 0 )
            {
                std::cout << iter->first << ' ' ;
                for( auto& v : graph.find(iter->first)->second ) --num_pred_map[v] ;
                iter = num_pred_map.erase(iter) ;
                cyclic = false ;
            }
            else ++iter ;
        }

        if(cyclic)
        {
            std::cerr << "graph is cyclic - nodes " ;
            for( auto& pair : num_pred_map ) std::cout << pair.first << ' ' ;
            std::cout << '\n' ;
            return false ;
        }
    }
    std::cout << '\n' ;
    return true ;
}

int main()
{
    std::istringstream stm( "1 2   1 7   1 8   2 3   2 6   2 10  3 4   3 5   3 11   "
                            "6 10   6 12  8 9   8 12   9 10   9 11   11 7   12 5" ) ;
    adjacency_list graph = create(stm) ;

    std::cout << "top sort => " ; topological_sort(graph) ;
}
