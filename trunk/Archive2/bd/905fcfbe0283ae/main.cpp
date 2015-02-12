#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iostream>
using namespace std;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> MyGraph;
typedef boost::graph_traits<MyGraph>::vertex_descriptor MyVertex;

class MyVisitor : public boost::default_dfs_visitor
{
public:
  void discover_vertex(MyVertex v, const MyGraph& g) const
  {
    cerr << v << endl;
    return;
  }
};

int main()
{
  MyGraph g;
  boost::add_edge(0, 1, g);
  boost::add_edge(0, 2, g);
  boost::add_edge(1, 2, g);
  boost::add_edge(1, 3, g);

  MyVisitor vis;
  boost::depth_first_search(g, boost::visitor(vis));

  return 0;
}