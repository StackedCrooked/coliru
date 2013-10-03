#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

int main()
{
    std::istringstream cin("6 9 \n1 6 1 \n1 2 2 \n1 4 3 \n2 3 3 \n2 5 2 \n3 4 4 \n3 6 2 \n4 5 5 \n5 6 4 \n4\n");
    
    using namespace boost;
    // a few helpful typedefs
    typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                           property<edge_weight_t, int> > graph_t;
    typedef graph_traits<graph_t>::edge_descriptor edge_t;
    
    int n, m;
    cin >> n >> m;

    graph_t g(m);

    // load the data into the graph
    property_map<graph_t, edge_weight_t>::type wmap = get(edge_weight, g);
    while(m-->0) {
        int i, j, w;
        cin >> i >> j >> w;
        wmap[add_edge(i, j, g).first] = -w;
    }
    int k;
    cin >> k;

    // find MST
    std::vector<edge_t> mst;
    kruskal_minimum_spanning_tree(g, std::back_inserter(mst));

    // print the number of channels that need widening
    std::cout << count_if(mst.begin(), mst.end(), [&](edge_t e){
        return wmap[e] > -k;
    });
}
