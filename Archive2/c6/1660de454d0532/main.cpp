#include<iostream>
#include<vector>
#include<boost/config.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list < vecS,vecS,directedS,no_property,property < edge_weight_t,int> > Graph;

typedef graph_traits < Graph >::vertex_descriptor Vertex;
typedef graph_traits < Graph >::edge_descriptor Edge;

const int nnodes=5;
const int nedges=8;

const int EDGE[nedges][3]={{0, 1, 1}, {0, 2, 5}, {1, 2, 4}, {1, 3, 2},{2, 4, 3}, {3, 2, 1}, {3, 4, 7}, {4, 0, 1}};

const int SOURCE=0;
const int TARGET=4;

int main()
{
    Graph g(nnodes);
    property_map < Graph, edge_weight_t >::type weightMap=get(edge_weight,g);

    for(int i=0;i<nedges;i++)
    {
        bool success;
        Edge e;
        tie(e,success)=add_edge(EDGE[i][0],EDGE[i][1],g);
        weightMap[e]=EDGE[i][2];
    }

    vector < Vertex > predecessor(num_vertices(g));
    vector < int > distances(num_vertices(g));

    dijkstra_shortest_paths(g,SOURCE,predecessor_map(&predecessor[0]).distance_map(&distances[0]));

    cout<<"Distances from Source to all nodes"<<endl;
    for(int i=0;i<nnodes;i++)
    {
        cout<<SOURCE<<"to"<<i<<"="<<distances[i]<<endl;
    }
    cout<<"shortest distance from source to target"<<endl;
    int curr=TARGET;
    cout<<curr;
    while(curr!=SOURCE)
    {
        cout<<"<-"<<(curr=predecessor[curr]);
    }
    cout << endl;
}