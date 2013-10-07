#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <utility>

struct Vertex
{
  std::string code;
};

struct Edge
{
  double distance;
  std::string code;
};

int main()
{
  using namespace boost;
  typedef adjacency_list<multisetS , vecS, undirectedS, Vertex, Edge> Graph;
  Graph g;
  auto a= add_vertex(Vertex{ "A" }, g);
  auto b= add_vertex(Vertex{ "B" }, g);
  auto c= add_vertex(Vertex{ "C" }, g);
  add_edge(a, b, Edge{ 10, "E1" }, g);
  add_edge(a, b, Edge{ 10, "E2" }, g);
  add_edge(a, b, Edge{ 10, "E3" }, g);
  add_edge(a, c, Edge{ 10, "E4" }, g);

  // checking number of edges
  std::cout<< num_edges(g)<< std::endl;

  // printing edges branching from A
  auto erange= out_edges(a, g);
  for(auto i= erange.first; i!= erange.second; ++ i)
    std::cout<< g[*i].code<< std::endl;

  // now we want to iterate over edges that connect A and B
  auto wtf= boost::edge_range(a, b, g);
  for(auto i= wtf.first; i!= wtf.second; ++ i)
    std::cout<< g[*i].code<< std::endl;
}