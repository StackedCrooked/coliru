/*
    Implementation for DFS, BFS and Djkstra
    g++ -o graph graph.cpp -std=c++11 -Wall -O2
    
Author :
    Prashant Srivastava
 
*/

#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <limits>
#include <algorithm>

class Graph {

public :
    Graph( int size ) : size(size) 
    {
        g_ = new std::list<Edge> [size] ;
    }
    ~Graph()
    {
        delete [] g_;
    }
    void addEdge( int i, int j, int w=1)
    {
        Edge e(i,j,w);
        g_[i].push_back( e );
    }

    void dispGraph( void );
    void  dfs( int source, int destination )  ;
    void  bfs( int source, int destination )  ;
    std::vector<int>  djkstra( int source, int destination );
    Graph(const Graph& g_) = delete ;
    Graph& operator=(const Graph& ) =delete ;

private:
    struct Edge{
        int from ;
        int to;
        int weight;
        Edge( int f, int t, int w=1):from(f),to(t),weight(w)
        {
        
        }
    };

    std::list<Edge> *g_;
    int size;
    
};

void Graph::dispGraph( void )
{
    for(int x=0; x<size; ++x )
        for(const auto& y:g_[x])
            std::cout << "( "<< y.from <<", "<< y.to << ", " << y.weight << " )" << std::endl ;
}


void Graph::dfs( int source, int destination=-1 )
{
    std::stack<int> S;
    bool *visited = new bool[size];
    for( int i =0 ;i < size ; i++)
        visited[i] = false ;
    
    S.push( source );
    
    while ( !S.empty() )
    {
        int x = S.top();
        S.pop();
 
        if( !visited[x] )
        {
            std::cout << x << " ";
            if(x == destination )
            {   std::cout << std::endl;
                return ;
            }
            visited[x] = true ;
            for ( const auto &it:g_[x] )
            {   
                S.push( it.to ) ;
            }
        }
    }
    
    std::cout << std::endl ;
    delete [] visited;
}

void Graph::bfs(int source, int destination=-1 )
{
    std::queue<int> Q;
    
    bool *visited = new bool[size];
    for( int i =0 ;i < size ; i++)
        visited[i] = false ;
    
    Q.push( source );
    visited[ source ] = true ;
    
    while ( !Q.empty() )
    {
        int x = Q.front() ;
        Q.pop( );
        std::cout << x <<" ";
        if(x == destination )
        {   std::cout << std::endl;
            return ;
        }
        for ( const auto &it:g_[x] )
            if( !visited[it.to] ) 
            {
                Q.push( it.to );
                visited[ it.to ] = true ;
            }
    }
    
    std::cout << std::endl ;
    delete [] visited;
}

std::vector<int> Graph::djkstra( int source, int destination =-1)
{
    typedef std::pair<int,int> Node;
    
    std::priority_queue<Node, std::vector<Node>, std::greater<Node> > Q;
    std::vector<int> parent(size);
    std::vector<int> path;
    
    int *dist = new int[size];
    for( int i =0 ;i < size ; i++)
        dist[i] = std::numeric_limits<int>::max() ;
    
    dist[source] = 0;
    Q.push({ dist[source], source} );
   
    while ( !Q.empty() )
    {
        Node temp = Q.top() ;
        Q.pop();
        
        if( temp.second == destination )
        {
            break ;
        }
        for( const auto&it:g_[temp.second] )
        {
            if( dist[it.to] > it.weight + temp.first )
            {
                dist[it.to] = it.weight + temp.first ;
                Q.push( {dist[it.to], it.to} );
                parent[it.to] = temp.second ;
            }
            
        }
    }
    // for( int i=1; i<size; i++) 
        // std::cout<<"Node "<< i <<", min weight = "<<dist[i] << std::endl ;
    
    path.clear();
    int p = destination;
    path.push_back(destination);
    while(p != source)
    {
         p = parent[p];
         path.push_back(p);
    }
    

    delete [] dist;
    return path ;
}

int main()
{
 
    // Graph g(4);

    // g.addEdge(0, 1);
    // g.addEdge(0, 2);
    // g.addEdge(1, 2);
    // g.addEdge(2, 0);
    // g.addEdge(2, 3);
    // g.addEdge(3, 3);
    // g.dispGraph( );

    // g.dfs(2);
    // g.bfs(2);
    // g.djkstra(2,1) ;
    
    // Graph g(8);
    // g.addEdge(1,5,10);
    // g.addEdge(1,2,8);
    // g.addEdge(2,3,3);
    // g.addEdge(2,5,5);
    // g.addEdge(2,4,2);
    // g.addEdge(3,7,2);
    // g.addEdge(3,4,2);
    // g.addEdge(4,5,5);
    // g.addEdge(4,7,5);
    // g.addEdge(4,6,10);
    // g.addEdge(5,6,13);
    // g.addEdge(6,7,9);
    
    // g.dfs(1);
    // g.bfs(1);
    // std::vector<int> p= g.djkstra(1,6) ;
    // for_each( p.rbegin(), p.rend(), 
                    // [](const int& x){
                    // std::cout << x<<" ";
                // } );
    
    
    Graph g(5) ;
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.dispGraph( );
    g.dfs(1);
    g.bfs(3,1);
    return 0;
}